## Lab2 :checkered_flag: Project 1: Finding Lane Lines on the Road

Key Concepts: Deep Learning, Convolutional Neural Network(CNN), LeNet Architecture, Max
<hr>

### Overview 

In this Lab, You're now going to put together everything you've learned and implement the LeNet architecture using TensorFlow to classify 0-9 digits from 55000-5000-10000 (training-validation-testing) samples.



### The Processing Stepos
An MNIST image is initially 784 features (1D). If the data is not normalized from [0, 255] to [0, 1], normalize it. We reshape this to (28, 28, 1) (3D), and pad the image with 0s such that the height and width are 32 (centers digit further). Thus, the input shape going into the first convolutional layer is 32x32x1.

Specs
Convolution layer 1. The output shape should be 28x28x6.
Activation 1. Your choice of activation function.
Pooling layer 1. The output shape should be 14x14x6.
Convolution layer 2. The output shape should be 10x10x16.
Activation 2. Your choice of activation function.
Pooling layer 2. The output shape should be 5x5x16.
Flatten layer. Flatten the output shape of the final pooling layer such that it's 1D instead of 3D. The easiest way to do is by using tf.contrib.layers.flatten, which is already imported for you.
Fully connected layer 1. This should have 120 outputs.
Activation 3. Your choice of activation function.
Fully connected layer 2. This should have 84 outputs.
Activation 4. Your choice of activation function.
Fully connected layer 3. This should have 10 outputs.
You'll return the result of the final fully connected layer from the LeNet function.

### Tips Conclusion

1. MNIST data: X_train, y_train = mnist.train.images, mnist.train.labels # X is data，y: Label
2. Image size:   print("Image Shape: {}".format(X_train[0].shape))
3. Normalize image size with Padding: 28x28x1--> Becasue LeNet accepts 32x32xC (color channels)
   X_train=np.pad(X_train, ((0,0),(2,2),(2,2),(0,0)), 'constant') # ROW/COLUMN +2
4. Visualize Image, squeeze:  image = X_train[index].squeeze()
5. Use Sklearn.utils to shuffle images: from sklearn.utils import shuffle
   X_train, y_train = shuffle(X_train, y_train)
6. Flatten multi-D images to 1-D using flatten func: tf.contrib.layers.flatten

