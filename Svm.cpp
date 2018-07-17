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


void getFiles(string filePath, vector<string> fileName)
{

}

/*
*	dataType: true for the pos, false for the neg
*	the samples are one-channel grayscale imgs and finally convert to CV32F1
*/
//void readFile(string filePath, Mat & dataSet, vector<int> & label, bool dataType, int maxFilePreIndex)
//{
//
//	for (int j = 1; j <= maxFilePreIndex; j++)
//	{
//		for (int i = 0; i< 5; i++)
//		{
//			// safely read the img
//			string fileName = to_string(j) + "_" + to_string(i) + ".jpg";
//			Mat src = imread(filePath + fileName, IMREAD_GRAYSCALE);
//			if (src.empty()) continue;
//			if (src.size().width > 50)
//				continue;
//
//			//push the label and data 
//			//temp_data.push_back(src.reshape(1, 1));
//			dataSet.push_back(src.reshape(1, 1));
//
//			if (dataType) label.emplace_back(1);
//			else label.emplace_back(0);
//		}
//	}
//}

void readPosFile(string filePath, Mat & dataSet, vector<int> & label)
{
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 1; j <= 1500; j++)
		{
			// safely read the img
			string fileName = to_string(i) + "_" + to_string(j) +".jpg";
			Mat src = imread(filePath + fileName, IMREAD_GRAYSCALE);
			if (src.empty()) continue;

			//push the label and data 
			//temp_data.push_back(src.reshape(1, 1));
			dataSet.push_back(src.reshape(1, 1));

			label.emplace_back(1);
		}
	}

}

void readNegFile(string filePath, Mat & dataSet, vector<int> & label, int Num)
{
	for (int i = 1; i <= Num; i++)
	{
		// safely read the img
		string fileName = to_string(i) + ".jpg";
		Mat src = imread(filePath + fileName, IMREAD_GRAYSCALE);
		if (src.empty()) continue;

		//push the label and data 
		//temp_data.push_back(src.reshape(1, 1));
		dataSet.push_back(src.reshape(1, 1));

		label.emplace_back(0);
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

	//Mat train_pos_data, train_neg_data, test_pos_data, test_neg_data;
	Mat train_data, test_data;
	Mat train_label, test_label;
	vector<int> train_label_vec, test_label_vec;

	//read the train data & regulate the format
	//readFile(filePath + filePathTrainPos, train_data, train_label_vec, true, 800);
	//readFile(filePath + filePathTrainNeg, train_data, train_label_vec, false, 300);
	readPosFile(filePath + filePathTrainPos, train_data, train_label_vec);
	int poSize = train_label_vec.size();
	readNegFile(filePath + filePathTrainNeg, train_data, train_label_vec, 6034);
	int neSize = train_label_vec.size() - poSize;
	Mat(train_label_vec).copyTo(train_label);
	train_data.convertTo(train_data, CV_32FC1);
	train_label.convertTo(train_label, CV_32SC1);
	transpose(train_label, train_label);

	////read the test data & regulate the format
	//readFile(filePath + filePathTestPos, test_data, test_label_vec, true, 800);
	//readFile(filePath + filePathTestNeg, test_data, test_label_vec, false, 300);
	//Mat(test_label_vec).copyTo(test_data);
	//test_data.convertTo(test_data, CV_32FC1);
	//test_label.convertTo(test_label, CV_32SC1);

	cout << "Data prepare successfully" << endl;
	cout << "positive samples :" << poSize <<endl;
	cout << "negtive samples :" << neSize << endl;

	/*
	*	2. Configure the SVM param
	*/
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER, 100, 1e-6));

	cout << "SVM Param config successfully" << endl;

	/*
	*	3. Train the SVM
	*/
	cout << "start to train the model" << endl;
	svm->train(train_data, SampleTypes::ROW_SAMPLE, train_label);
	cout << "model training finished" << endl;

	/*
	*	4. Save the model
	*/
	//svm->save("C:/Users/cooper/Desktop/Resp_for_ML/ML-method-for-Judging-Armor-Pattern/SVM.xml");
	svm->save("C:/Users/cooper/Desktop/Resp_for_ML/ML-method-for-Judging-Armor-Pattern/SVM3.xml");

	cout << "model saved" << endl;

	system("pause");
}














//vector<int> temp_label;
//Mat temp_data;
//
//vector<string> files;
//getFiles(filePath, files);
//int data_size = files.size();
//
//if (data_size == 0)
//{
//	cout << "Error: empty directory" << endl;
//}
//
//for (int i = 0; i < data_size; i++)
//{
//	// safely read the file
//	cout << files[i].c_str() << endl;
//	Mat src = imread(files[i].c_str);
//	if (src.size().width > 50) continue;
//
//	//push the label and data 
//	temp_data.push_back(src.reshape(1, 1));
//	temp_data.copyTo(dataSet);
//
//	if (dataType) temp_label.emplace_back(1);
//	else temp_label.emplace_back(0);
//	Mat(temp_label).copyTo(label);
//
//	// regulate the format
//	dataSet.convertTo(dataSet, CV_32FC1);
//	label.convertTo(label, CV_32SC1);
//}