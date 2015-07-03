/*
 * Utils.cpp
 *
 *  Created on: 2014年10月15日
 *      Author: netbeen
 */


#include "ESR.hpp"

using namespace std;
using namespace cv;

//从所有的shape中得到mean shape
Mat_<double> getMeanShape(const vector<Mat_<double> >& shapes, const vector<BoundingBox>& bounding_box) {
	cout << "Starting GetMeanShape..." <<endl;
	Mat_<double> result = Mat::zeros(shapes[0].rows, 2, CV_64FC1);
    for (int i = 0; i < static_cast<int>(shapes.size()); i++) {
		result = result + projectShape(shapes[i], bounding_box[i]);
	}
	result = 1.0 / shapes.size() * result;
	return result;
}

Mat_<double> projectShape(const Mat_<double>& shape, const BoundingBox& bounding_box) {
	Mat_<double> temp(shape.rows, 2);
	for (int j = 0; j < shape.rows; j++) {
		temp(j, 0) = (shape(j, 0) - bounding_box.centerX) / (bounding_box.width / 2.0);
		temp(j, 1) = (shape(j, 1) - bounding_box.centerY) / (bounding_box.height / 2.0);
	}
	return temp;
}

Mat_<double> reProjectShape(const Mat_<double>& shape, const BoundingBox& bounding_box) {
	Mat_<double> temp(shape.rows, 2);
	for (int j = 0; j < shape.rows; j++) {
		temp(j, 0) = (shape(j, 0) * bounding_box.width / 2.0 + bounding_box.centerX);
		temp(j, 1) = (shape(j, 1) * bounding_box.height / 2.0 + bounding_box.centerY);
	}
	return temp;
}

void SimilarityTransform(const Mat_<double>& shape1, const Mat_<double>& shape2, Mat_<double>& rotation, double& scale) {
	rotation = Mat::zeros(2, 2, CV_64FC1);
	scale = 0;

	// center the data
	double center_x_1 = 0;
	double center_y_1 = 0;
	double center_x_2 = 0;
	double center_y_2 = 0;
	for (int i = 0; i < shape1.rows; i++) {
		center_x_1 += shape1(i, 0);
		center_y_1 += shape1(i, 1);
		center_x_2 += shape2(i, 0);
		center_y_2 += shape2(i, 1);
	}
	center_x_1 /= shape1.rows;
	center_y_1 /= shape1.rows;
	center_x_2 /= shape2.rows;
	center_y_2 /= shape2.rows;

	Mat_<double> temp1 = shape1.clone();
	Mat_<double> temp2 = shape2.clone();
	for (int i = 0; i < shape1.rows; i++) {
		temp1(i, 0) -= center_x_1;
		temp1(i, 1) -= center_y_1;
		temp2(i, 0) -= center_x_2;
		temp2(i, 1) -= center_y_2;
	}

	Mat_<double> covariance1, covariance2;	//covariance = 协方差
	Mat_<double> mean1, mean2;
	// calculate covariance matrix
	calcCovarMatrix(temp1, covariance1, mean1, CV_COVAR_COLS);	//计算temp1的协方差
	calcCovarMatrix(temp2, covariance2, mean2, CV_COVAR_COLS);

	double s1 = sqrt(norm(covariance1));
	double s2 = sqrt(norm(covariance2));
	scale = s1 / s2;
	temp1 = 1.0 / s1 * temp1;
	temp2 = 1.0 / s2 * temp2;

	double num = 0;
	double den = 0;
	for (int i = 0; i < shape1.rows; i++) {
		num = num + temp1(i, 1) * temp2(i, 0) - temp1(i, 0) * temp2(i, 1);
		den = den + temp1(i, 0) * temp2(i, 0) + temp1(i, 1) * temp2(i, 1);
	}

	double norm = sqrt(num * num + den * den);
	double sin_theta = num / norm;
	double cos_theta = den / norm;
	rotation(0, 0) = cos_theta;
	rotation(0, 1) = -sin_theta;
	rotation(1, 0) = sin_theta;
	rotation(1, 1) = cos_theta;
}

double calculate_covariance(const vector<double>& v_1, const vector<double>& v_2) {
	assert(v_1.size() == v_2.size());
	assert(v_1.size() != 0);
	double sum_1 = 0;
	double sum_2 = 0;
	double exp_1 = 0;
	double exp_2 = 0;
	double exp_3 = 0;
    for (int i = 0; i < static_cast<int>(v_1.size()); i++) {
		sum_1 += v_1[i];
		sum_2 += v_2[i];
	}
	exp_1 = sum_1 / v_1.size();
	exp_2 = sum_2 / v_2.size();
    for (int i = 0; i < static_cast<int>(v_1.size()); i++) {
		exp_3 = exp_3 + (v_1[i] - exp_1) * (v_2[i] - exp_2);
	}
	return exp_3 / v_1.size();
}
