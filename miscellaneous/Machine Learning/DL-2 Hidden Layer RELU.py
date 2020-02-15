import tensorflow as tf
import math

from tensorflow.examples.tutorials.mnist import input_data
mnist=input_data.read_data_sets(",",one_hot=True, reshape=False)

# Learning Parameters
learning_rate=0.001
training_epochs=20
batch_size=128
display_step=5

n_input=784  #MNIST data input 28*28 img_shape
n_classes=10 # MNIST total classes (0-9 digits)

# Hidden_layer Parameters
n_hidden_layer=200 #256 #layer # of features: determine the size of the hidden layer (width of a layer)

# Weights & Biases in Dict Type
weights={'hidden_layer':tf.Variable(tf.random_normal([n_input,n_hidden_layer])),
         'out':tf.Variable(tf.random_normal([n_hidden_layer,n_classes]))}  #random_normal (tensor_size)
biases={'hidden_layer':tf.Variable(tf.zeros(n_hidden_layer)),
        'out':tf.Variable(tf.zeros(n_classes))}
# Deep Neural network use multiple layers. with each layer requires its own weights and bias

# TF Graph input
x=tf.placeholder("float",[None,28,28,1]) # repesent N*28*28*1
y=tf.placeholder("float",[None,n_classes]) # represent N*n_classes

x_flat=tf.reshape(x,[-1, n_input]) # reshapes above 28x28 image matrices in x into row vectors of 784
# 784 elements as in 1 row  x n_rows (ie. None above)

# Multilayer Perceptron  -- combine linear functions together using a Relu --> give a 2 layer network
layer_1=tf.add(tf.matmul(x_flat,weights['hidden_layer']),biases['hidden_layer'])
   # Hidden layer with Relu activation
layer_1=tf.nn.relu(layer_1)
   # Output layer with linear activation
logits=tf.add(tf.matmul(layer_1,weights['out']),biases['out'])

# Optimizer
cost=tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=logits,labels=y))
optimizer=tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cost)

# Session
init=tf.global_variables_initializer()

with tf.Session() as sess:
    #initialize
    sess.run(init)
    # Training Cycle
    for epoch in range(training_epochs):
        total_batch=int(mnist.train.num_examples/batch_size)
        # total_batch=math.ceil(mnist.train.num_examples/batch_size)
        #loop over all batchesd
        for i in range(total_batch):
            # batch_x:batch features, batch_y:batch_labels
            batch_x,batch_y=mnist.train.next_batch(batch_size) #return a subset of the training data  
                  
            #Run optimization op(backprop) and cosr op (to get loss value)
            sess.run(optimizer,feed_dict={x:batch_x,y:batch_y})
        # Display logs per epoch step
        if epoch % display_step==0:  # residual
            c=sess.run(cost,feed_dict={x:batch_x,y:batch_y})
            print("Epoch:",'%04d'%(epoch+1),"cost=","{:.9f}".format(c)) # 4digits
        print("Optimization Finished!")

    # Test model
    correct_prediction = tf.equal(tf.argmax(logits,1),tf.argmax(y,1))
    # Calculate accuracy
    accuracy=tf.reduce_mean(tf.cast(correct_prediction,"float"))
    # Decrease test size if memory is limited
    test_size=100
    print("Accuracy: ", accuracy.eval({x:mnist.test.images[:test_size], y:mnist.test.labels[:test_size]}))
