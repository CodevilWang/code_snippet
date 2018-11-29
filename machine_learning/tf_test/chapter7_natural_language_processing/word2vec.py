#!usr/bin/env python
import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import random
import os
import string
import requests
import collections
import io
import tarfile
from urllib2 import urlopen
from nltk.corpus import stopwords
sess = tf.Session()
batch_size = 50
embedding_size = 200
vocabulary_size = 10000
generations = 50000
print_loss_every = 500
num_sampled = int(batch_size / 2)
window_size = 2
stops = stopwords.words('english')
print_valid_every = 2000
valid_words = ['cliche', 'love', 'hate', 'silly', 'sad']


def load_movie_data():
    save_folder_name = './temp'
    pos_file = os.path.join(save_folder_name, 'rt-polarity.pos')
    neg_file = os.path.join(save_folder_name, 'rt-polarity.neg')
    if os.path.exists(save_folder_name) and os.path.exists(pos_file):
        pos_data = []
        with open(pos_file, 'r') as temp_pos_file:
            for row in temp_pos_file:
                pos_data.append(row)
        neg_data = []
        with open(neg_file, 'r') as temp_neg_file:
            for row in temp_neg_file:
                neg_data.append(row)
    else:
        movie_data_url = 'http://www.cs.cornell.edu/people/pabo/movie-review-data/rt-polaritydata.tar.gz'
        stream_data = urlopen(movie_data_url)
        tmp = io.BytesIO()
        while True:
            s = stream_data.read(16384)
            if not s:
                break
            tmp.write(s)
        stream_data.close()
        tmp.seek(0)
        tar_file = tarfile.open(fileobj = tmp, mode = 'r:gz')
        pos = tar_file.extractfile('rt-polaritydata/rt-polarity.pos')
        neg = tar_file.extractfile('rt-polaritydata/rt-polarity.neg')
        pos_data = []
        for line in pos:
            pos_data.append(line.decode('ISO-8859-1').encode('ascii', errors = 'ignore').decode())
        neg_data = []
        for line in neg:
            neg_data.append(line.decode('ISO-8859-1').encode('ascii', errors = 'ignore').decode())
        tar_file.close()
        if not os.path.exists(save_folder_name):
            os.makedirs(save_folder_name)
        with open(pos_file, 'w') as pos_file_handler:
            pos_file_handler.write(''.join(pos_data))
        with open(neg_file, 'w') as neg_file_handler:
            neg_file_handler.write(''.join(neg_data))
    texts = pos_data + neg_data
    target = [1] * len(pos_data) + [0] * len(neg_data)
    return (texts, target)

texts, target = load_movie_data()
def normalize_text(texts, stops):
    texts = [x.lower() for x in texts]
    texts = [''.join(c for c in x if c not in string.punctuation) for x in texts]
    texts = [''.join(c for c in x if c not in '0123456789') for x in texts]
    texts = [' '.join([word for word in x.split() if word not in (stops)]) for x in texts]
    texts = [' '.join(x.split()) for x in texts]
    return texts

texts = normalize_text(texts, stops)
targets = [target[ix] for ix, x in enumerate(texts) if len(x.split()) > 2]
texts = [x for x in texts if len(x.split()) > 2]

def build_dictionary(sentences, vocabulary_size):
    split_sentences = [s.split() for s in sentences]
    words = [x for sublist in split_sentences for x in sublist]
    count = [['RARE', -1]]
    count.extend(collections.Counter(words).most_common(vocabulary_size - 1))
    word_dict = {}
    for word, word_count in count:
        word_dict[word] = len(word_dict)
    return word_dict

def text_to_numbers(sentences, word_dict):
    data = []
    for sentence in sentences:
        sentence_data = []
        for word in sentence: 
            if word in word_dict:
                word_ix = word_dict[word]
            else:
                word_ix = 0
            sentence_data.append(word_ix)
        data.append(sentence_data)
    return data

word_dictionary = build_dictionary(texts, vocabulary_size)
word_dictionary_rev = dict(zip(word_dictionary.values(), word_dictionary.keys()))
text_data = text_to_numbers(texts, word_dictionary)
valid_examples = [word_dictionary[x] for x in valid_words]

def generate_batch_data(sentences, batch_size, window_size, method = 'skip_gram'):
    batch_data = []
    label_data = []
    while len(batch_data) < batch_size:
        rand_sentences = np.random.choice(sentences)
        window_sequences = [rand_sentences[max((ix - window_size), 0) : (ix + window_size + 1)] for \
                ix, x in enumerate(rand_sentences)]
        label_indices = [ix if ix < window_size else window_size for ix, x in \
                enumerate(window_sequences)]
        if method == 'skip_gram':
            batch_and_labels = [(x[y], x[:y] + x[(y+1) : ]) for x, y in zip(window_sequences, label_indices)]
            tuple_data = [(x, y_) for x,y in batch_and_labels for y_ in y]
        else:
            raise ValueError('Method {} not implemented yet.'.format(method))

        batch, labels = [list(x) for x in zip(*tuple_data)]
        batch_data.extend(batch[:batch_size])
        label_data.extend(labels[:batch_size])
    batch_data = batch_data[:batch_size]
    label_data = label_data[:batch_size]
    batch_data = np.array(batch_data)
    label_data = np.transpose(np.array([label_data]))
    return batch_data, label_data

embeddings = tf.Variable(tf.random_uniform([vocabulary_size, embedding_size], -1.0, 1.0))
x_inputs = tf.placeholder(tf.int32, shape = [batch_size])
print x_inputs.shape
y_target = tf.placeholder(tf.float32, shape = [batch_size, 1])
print y_target.shape
valid_dataset = tf.constant(valid_examples, dtype = tf.int32)
embed = tf.nn.embedding_lookup(embeddings, x_inputs)
nce_weights = tf.Variable(tf.truncated_normal([vocabulary_size, embedding_size], stddev = 1.0 / np.sqrt(embedding_size)))
nce_biases = tf.Variable(tf.zeros([vocabulary_size]))
print nce_weights.shape
print nce_biases.shape
loss = tf.reduce_mean(tf.nn.nce_loss(nce_weights, nce_biases, y_target, embed, num_sampled, vocabulary_size))

norm = tf.sqrt(tf.reduce_sum(tf.square(embeddings), 1, keep_dims = True))
normalized_embeddings = embeddings / norm
valid_embeddings = tf.nn.embedding_lookup(normalized_embeddings, valid_dataset)
similarity = tf.matmul(valid_embeddings, normalized_embeddings, transpose_b = True)

optimizer = tf.train.GradientDescentOptimizer(learning_rate = 1.0).minimize(loss)
init = tf.initialize_all_variables()
sess.run(init)

loss_vec = []
loss_x_vec = []
for i in range(generations):
    batch_inputs, batch_labels = generate_batch_data(text_data, batch_size, window_size)
    feed_dict = {x_inputs : batch_inputs, y_target : batch_labels}
    sess.run(optimizer, feed_dict = feed_dict)
    if (i + 1) % print_loss_every == 0:
        loss_val = sess.run(loss, feed_dict = feed_dict)
        loss_vec.append(loss_val)
        loss_x_vec.append(i + 1)
        print "Loss at step {} : {}".format(i + 1, loss_val)
    if (i + 1) % print_loss_every == 0:
        sim = sess.run(similarity, feed_dict = feed_dict)
        for j in range(len(valid_words)):
            valid_word = word_dictionary_rev[valid_examples[j]]
            top_k = 5
            nearest = (-sim[j, :]).argsort()[1 : top_k + 1]
            log_str = "Nearest to {}:".format(valid_word)
            for k in range(top_k):
                close_word = word_dictionary_rev[nearest[k]]
                log_str = '%s %s,' % (log_str, close_word)
            print (log_str)
