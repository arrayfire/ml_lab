#include <arrayfire.h>
#include <af/util.h>
#include "mnist_common.h"

using namespace std;
using namespace af;

// Activation function
array sigmoid(const array &val)
{
    return 1 / (1 + exp(-val));
}

int main()
{
    array train_images, train_targets;
    array test_images, test_targets;
    int num_train, num_test, num_classes;

    // Load mnist data
    setup_mnist<true>(&num_classes, &num_train, &num_test,
                      train_images, test_images,
                      train_targets, test_targets, 1);

    float learning_rate = 0.1f;

    //Initialize weights to 0
    const int pixel_count = 28*28;  //train_feat.dims(1);
    const int num_labels = 10;      //train_targest.dims(1);
    array weights = constant(0, num_labels, pixel_count);

    // Reshape images into feature vectors
    int feature_length = train_images.elements() / num_train;
    array train_feats = moddims(train_images, pixel_count, num_train);
    array test_feats  = moddims(test_images , pixel_count, num_test );

    for(int i = 0; i < 100; i++) {
        array prediction = sigmoid(matmul(weights, train_feats));
        array err = train_targets - prediction;
        float mean_abs_error = mean<float>(abs(err));

        printf("err: %0.4f\n", mean_abs_error);
        weights = weights + learning_rate * (matmulNT(err, train_feats));
    }

    // Predict the test data
    array test_outputs = sigmoid(matmul(weights, test_feats)).T();

    test_outputs = test_outputs.T();
    test_targets = test_targets;

    // Get 20 random test images.
    display_results<true>(test_images, test_outputs, test_targets, 20);

}
