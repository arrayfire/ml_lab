/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <arrayfire.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <af/util.h>
#include <math.h>
#include "mnist_common.h"

using namespace af;
using std::vector;

float accuracy(const array& predicted, const array& target)
{
    array val, plabels, tlabels;
    max(val, tlabels, target, 1);
    max(val, plabels, predicted, 1);
    return 100 * count<float>(plabels == tlabels) / tlabels.elements();
}

// Derivative of the activation function
array deriv(const array &out)
{
    return out * (1 - out);
}

// Cost function
double error(const array &out,
             const array &pred)
{
    array dif = (out - pred);
    return sqrt((double)(sum<float>(dif * dif)));
}


class rbm {

private:
    array weights;
    array h_bias;
    array v_bias;

public:
    rbm(int v_size, int h_size) :
        weights(randu(h_size, v_size)/100.f),
        h_bias(constant(0, 1, h_size)),
        v_bias(constant(0, 1, v_size))
    {
    }

    array get_weights()
    {
    }

    void train(const array &in, double lr, int num_epochs, int batch_size, bool verbose)
    {

    }

    array prop_up(const array &in)
    {
    }
};

class dbn {

private:
    const int in_size;
    const int out_size;
    const int num_hidden;
    const int num_total;
    std::vector<array> weights;
    std::vector<int> hidden;

    array add_bias(const array &in)
    {
    }

    vector<array> forward_propagate(const array& input)
    {
    }

    void back_propagate(const vector<array> signal,
                        const array &target,
                        const double &alpha)
    {
    }

public:

    dbn(const int in_sz, const int out_sz,
        const std::vector<int> hidden_layers) :
        in_size(in_sz),
        out_size(out_sz),
        num_hidden(hidden_layers.size()),
        num_total(hidden_layers.size() + 2),
        weights(hidden_layers.size() + 1),
        hidden(hidden_layers)
    {
    }

    void train(const array &input, const array &target,
               double lr_rbm = 1.0,
               double lr_nn  = 1.0,
               const int epochs_rbm = 15,
               const int epochs_nn = 300,
               const int batch_size = 100,
               double maxerr = 1.0, bool verbose=false)
    {
    }

    array predict(const array &input)
    {
        vector<array> signal = forward_propagate(input);
        array out = signal[num_total - 1];
        return out;
    }

};

int dbn_demo(bool console, int perc)
{
    printf("** ArrayFire DBN Demo **\n\n");

    array train_images, test_images;
    array train_target, test_target;
    int num_classes, num_train, num_test;

    // Load mnist data
    float frac = (float)(perc) / 100.0;
    setup_mnist<true>(&num_classes, &num_train, &num_test,
                      train_images, test_images, train_target, test_target, frac);

    int feature_size = train_images.elements() / num_train;

    // Reshape images into feature vectors
    array train_feats = moddims(train_images, feature_size, num_train).T();
    array test_feats  = moddims(test_images , feature_size, num_test ).T();

    train_target = train_target.T();
    test_target  = test_target.T();

    // Network parameters
    vector<int> layers;
    layers.push_back(100);
    layers.push_back(50);

    /////////////////////////////////////////////////
    // Create network


    // Benchmark prediction
    /////////////////////////////////////////////////

    //printf("\nTraining set:\n");
    //printf("Accuracy on training data: %2.2f\n",
    //       accuracy(train_output, train_target));

    //printf("\nTest set:\n");
    //printf("Accuracy on testing  data: %2.2f\n",
    //       accuracy(test_output , test_target ));

    //printf("\nTraining time: %4.4lf s\n", train_time);
    //printf("Prediction time: %4.4lf s\n\n", test_time);

    if (!console) {
        // Get 20 random test images.
        //test_output = test_output.T();
        //test_target = test_target.T();
        //display_results<true>(test_images, test_output, test_target, 20);
    }

    return 0;
}

int main(int argc, char** argv)
{
    int device   = argc > 1 ? atoi(argv[1]) : 0;
    bool console = argc > 2 ? argv[2][0] == '-' : false;
    int perc     = argc > 3 ? atoi(argv[3]) : 60;

    try {

        af::deviceset(device);
        af::info();
        return dbn_demo(console, perc);

    } catch (af::exception &ae) {
        std::cout << ae.what() << std::endl;
    }

}
