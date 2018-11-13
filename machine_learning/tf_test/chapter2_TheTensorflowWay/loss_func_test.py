#!/usr/bin/env python
import matplotlib.pyplot as plt
import tensorflow as tf
sess = tf.Session()
x_vals = tf.linspace(-1., 1., 500)
target = tf.constant(0.)
l2_y_vals = tf.square(target - x_vals)
l2_y_out = sess.run(l2_y_vals)

l1_y_vals = tf.abs(target - x_vals)
l1_y_out = sess.run(l1_y_vals)

x_array = sess.run(x_vals)
plt.plot(x_array, l2_y_out, 'b-', label = 'L2 loss')
plt.plot(x_array, l1_y_out, 'r-', label = 'L1 loss')
plt.show()
