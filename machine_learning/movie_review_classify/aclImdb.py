#!/usr/bin/env python
from __future__ import absolute_import
from __future__ import division 
from __future__ import print_function 

import json
import numpy as np
from keras import models
from keras import layers

def get_word_index(path = './aclImdb_word_index.json'):
    with open(path) as f:
        return json.load(f)

def load_data(path = 'aclimdb.npz', num_words = None, skip_top = 0, \
        seed = 113, start_char = 1, oov_char = 2, index_from = 3):
    with np.load(path) as f:
        x_train, labels_train = f['x_train'], f['y_train']
        x_test, labels_test = f['x_test'], f['y_test']
    np.random.seed(seed)
    indices = np.arange(len(x_train))
    np.random.shuffle(indices)
    x_train = x_train[indices]
    labels_train = labels_train[indices]
    indices = np.arange(len(x_test))
    np.random.shuffle(indices)
    x_test = x_test[indices]
    labels_test = labels_test[indices]
    xs = np.concatenate([x_train, x_test])
    labels = np.concatenate([labels_train, labels_test])
    if start_char is not None:
        xs = [[start_char] + [w + index_from for w in x] for x in xs]
    elif index_from:
        xs = [[w + index_from for w in x] for x in xs]

    if not num_words:
        num_words = max([max(x) for x in xs])

    if oov_char is not None:
        xs = [[w if (skip_top <= w < num_words) else oov_char for w in x] for x in xs]
    else:
        xs = [[w for w in x if skip_top <= w < num_words] for x in xs]
    idx = len(x_train)
    x_train, y_train = np.array(xs[:idx]), np.array(labels[:idx])
    x_test, y_test = np.array(xs[idx:]), np.array(labels[idx:])
    return (x_train, y_train), (x_test, y_test)

def vectorize_sequences(sequences, dimension = 10000):
    results = np.zeros((len(sequences), dimension))
    for i, seq in enumerate(sequences):
        results[i, seq] = 1 
    return results

if __name__ == "__main__":
    (train_data, train_labels), (test_data, test_labels) = load_data(num_words = 10000)
    word_index = get_word_index()
    reverse_word_index = dict([(value, key) for (key, value) in word_index.items()])
    x_train = vectorize_sequences(train_data)
    x_test = vectorize_sequences(test_data)

    y_train = np.asarray(train_labels).astype('float32')
    y_test = np.asarray(test_labels).astype('float32')
    model = models.Sequential()
    model.add(layers.Dense(128, activation = 'relu', input_shape = (10000, )))
    model.add(layers.Dense(64, activation = 'relu'))
    model.add(layers.Dense(32, activation = 'relu'))
    model.add(layers.Dense(16, activation = 'relu'))
    model.add(layers.Dense(1, activation = 'sigmoid'))
    model.compile(optimizer = 'rmsprop', loss = 'binary_crossentropy', metrics = ['accuracy'])
    model.fit(x_train, y_train, epochs = 4, batch_size = 512)
    results = model.evaluate(x_test, y_test)
    print(results)
    model.predict(x_test)

