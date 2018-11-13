#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
sess = tf.Session()
batch_size = 20
x_vals = np.random.normal(1, 0.1, 100)
y_vals = np.repeat(10., 100)
x_data = tf.placeholder(shape = [None, 1], dtype = tf.float32)
y_target = tf.placeholder(shape = [None, 1], dtype = tf.float32)
A = tf.Variable(tf.random_normal(shape = [1, 1]))
my_output = tf.matmul(x_data, A)
loss = tf.reduce_mean(tf.square(my_output - y_target))
my_opt = tf.train.GradientDescentOptimizer(0.02)
train_step = my_opt.minimize(loss)
loss_batch = []
init = tf.global_variables_initializer()
sess.run(init)
for i in range(100):
    rand_idx = np.random.choice(100, size = batch_size)
    rand_x = np.transpose([x_vals[rand_idx]])
    rand_y = np.transpose([y_vals[rand_idx]])
    sess.run(train_step, feed_dict = {x_data : rand_x, y_target : rand_y})
    if (i + 1) % 5 == 0:
        print 'Step #' + str(i + 1) + ' A = ' + str(sess.run(A))
        temp_loss = sess.run(loss, feed_dict = {x_data : rand_x, y_target : rand_y})
        print "Loss = " + str(temp_loss)
        loss_batch.append(temp_loss)

from tensorflow.python.framework import ops
ops.reset_default_graph()
sess = tf.Session()
A = tf.Variable(tf.random_normal(shape = [1]))
x_data = tf.placeholder(shape = [1], dtype = tf.float32)
y_target = tf.placeholder(shape = [1], dtype = tf.float32)
my_opt = tf.train.GradientDescentOptimizer(0.02)
my_output = tf.multiply(x_data, A)
loss = tf.reduce_mean(tf.square(my_output - y_target))
train_step = my_opt.minimize(loss)
loss_sig = []
init = tf.global_variables_initializer()
sess.run(init)
for i in range(100):
    rand_idx = np.random.choice(100)
    rand_x = [x_vals[rand_idx]]
    rand_y = [y_vals[rand_idx]]
    sess.run(train_step, feed_dict = {x_data : rand_x, y_target : rand_y})
    if (i + 1) % 5 == 0:
        print 'Step #' + str(i + 1) + ' A = ' + str(sess.run(A))
        temp_loss = sess.run(loss, feed_dict = {x_data : rand_x, y_target : rand_y})
        print "Loss = " + str(temp_loss)
        loss_sig.append(temp_loss)
plt.plot(range(0, 100, 5), loss_sig, 'b-', label = "Stochastic Loss")
plt.plot(range(0, 100, 5), loss_batch, 'r--', label = "Batch Loss, size = 20")
plt.legend(loc = 'upper right', prop = {'size' : 11})
plt.show()

