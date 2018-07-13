#include<opencv2\opencv.hpp>
#include<opencv2\ml.hpp>
#include<iostream>
using namespace  std;
using namespace cv;
using namespace cv::ml;

/*
 the standard format of file directory is :
 --D:
	--data_svm
		--train
			--pos
			--neg
		--test
			--pos
			--neg
*/

/*
*	dataType: true for the pos, false for the neg
*/
void readFile(string filePath, Mat & dataSet, Mat & label, bool dataType, int maxFilePreIndex)
{
	vector<int> temp_label;
	vector<Mat> temp_data;
	for (int j = 1; j <= maxFilePreIndex; j++)
	{
		for (int i = 0; ; i++)
		{
			// safely read the img
			string fileName = to_string(j) + "_" + to_string(i) + ".jpg";
			Mat src = imread(filePath + fileName);
			if (src.empty()) break;
			if (src.size().width > 50)
				continue;

			//push the label and data 
			temp_data.emplace_back(src.reshape(1, 1));
			Mat(temp_data).copyTo(dataSet);
			
			if (dataType) temp_label.emplace_back(1);
			else temp_label.emplace_back(0);
			Mat(temp_label).copyTo(label);

			// regulate the format
			dataSet.convertTo(dataSet, CV_32FC1);
			label.convertTo(label, CV_32SC1);
			
		}
	}
}


int main()
{

	/*
	*	1. Perpare the data & label
	*/

	string filePath = "D:/possible_armor_area/";
	string filePathTrainPos = "data_svm/train/pos/";
	string filePathTrainNeg = "data_svm/train/neg/";
	string filePathTestPos = "data_svm/test/pos/";
	string filePathTestNeg = "data_svm/test/neg/";

	Mat train_pos_data, train_neg_data, test_pos_data, test_neg_data;
	Mat train_label, test_label;

	//read the train data & regulate the format
	readFile(filePath + filePathTrainPos, train_pos_data, train_label, true, 800);
	readFile(filePath + filePathTrainNeg, train_neg_data, train_label, false, 300);

	//read the test data & regulate the format
	readFile(filePath + filePathTestPos, test_pos_data, test_label, true, 800);
	readFile(filePath + filePathTestNeg, test_neg_data, test_label, false, 300);

	

	/*
	*	2. Configure the SVM param
	*/
	

}