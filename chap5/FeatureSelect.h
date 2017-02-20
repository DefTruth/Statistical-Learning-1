#pragma once
#ifndef FEATURESELECT_H
#define FEATURESELECT_H

#include "my_funtion.h"

class FeatureSelect
{
public:
	FeatureSelect();
	FeatureSelect(vector<vector<int>>& _data, vector<int>&_kind,vector<string>&_name);
	~FeatureSelect();
	void Statistics();
	vector<map<int, double>>feature_count;
	vector<vector<int>>feature;
	vector<vector<int>>data;
	vector<int>kind;
	vector<double>conditional_entropy;
	vector<double>gain;
	vector<double>gain_ratio;
	pair<bool, int> only_one_Ck;//����ʵ������ͬһ�࣬����Ck����
	map<int, set<int>>feature_value;//ÿ�������Ŀ���ȡֵ
	vector<string>name;
	double empirical_entropy;
	int max_gain_kind;
	bool no_feature;//û������ֵ����ʵ����������Ck����
	int max_kind;
private:

};




#endif