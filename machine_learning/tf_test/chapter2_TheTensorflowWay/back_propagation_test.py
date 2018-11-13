#!/usr/bin/env python
import numpy as np
import tensorflow as tf
# regression
sess = tf.Session()
x_vals = np.random.normal(1, 0.1, 100)
y_vals = np.repeat(10., 100)
x_data = tf.placeholder(shape = [1], dtype = tf.float32)
y_target = tf.placeholder(shape = [1], dtype = tf.float32)
A = tf.Variable(tf.random_normal(shape = [1]))
my_output = tf.multiply(x_data, A)
loss = tf.square(my_output - y_target)
init = tf.initialize_all_variables()
sess.run(init)
my_opt = tf.train.GradientDescentOptimizer(learning_rate = 0.02)
train_step = my_opt.minimize(loss)
print "Regression."
for i in range(100):
    rand_idx = np.random.choice(100)
    rand_x = [x_vals[rand_idx]]
    rand_y = [y_vals[rand_idx]]
    sess.run(train_step, feed_dict = {x_data : rand_x, y_target : rand_y})
    if (i + 1) % 25 == 0:
        print "Step #" + str(i + 1) + ' A = ' + str(sess.run(A))
        print "Loss #" + str(i + 1) + ' loss = ' + str(sess.run(loss, \
                                                                feed_dict = {x_data : rand_x, y_target : rand_y}))

# classification
print "Classification."
from tensorflow.python.framework import ops
ops.reset_default_graph()
sess = tf.Session()
x_vals = np.concatenate((np.random.normal(-1, 1, 50), np.random.normal(3, 1, 50)))
y_vals = np.concatenate((np.repeat(0., 50), np.repeat(1., 50)))
x_data = tf.placeholder(shape = [1], dtype = tf.float32)
y_target = tf.placeholder(shape = [1], dtype = tf.float32)
A = tf.Variable(tf.random_normal(mean = 10, shape = [1]))
my_output = tf.add(x_data, A)
my_output_expanded = tf.expand_dims(my_output, 0)
y_target_expanded = tf.expand_dims(y_target, 0)
# print my_output.shape
# print my_output_expanded.shape
# print y_target.shape
# print y_target_expanded.shape
init = tf.initialize_all_variables()
sess.run(init)
xentropy = tf.nn.sigmoid_cross_entropy_with_logits(logits = my_output_expanded, labels = y_target_expanded)
# xentropy = tf.nn.sigmoid_cross_entropy_with_logits(logits = my_output, labels = y_target)
my_opt = tf.train.GradientDescentOptimizer(0.05)
train_step = my_opt.minimize(xentropy)
for i in range(1400):
    rand_idx = np.random.choice(100)
    rand_x = [x_vals[rand_idx]]
    rand_y = [y_vals[rand_idx]]
    sess.run(train_step, feed_dict = {x_data : rand_x, y_target : rand_y})
    if (i + 1) % 200 == 0:
        print "Step #" + str(i + 1) + ' A = ' + str(sess.run(A))
        print "Loss =" + str(sess.run(xentropy, feed_dict = {x_data : rand_x, y_target : rand_y}))
