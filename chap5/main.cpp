
#include "my_funtion.h"

//#include "FeatureSelect.h"
#include "DecisionTree.h" 

int main()
{
	vector<vector<int>>data{
	{0,0,0,0},
	{0,0,0,1},
	{0,1,0,1},
	{0,1,1,0},
	{0,0,0,0},
	{1,0,0,0},
	{1,0,0,1},
	{1,1,1,1},
	{1,0,1,2},
	{1,0,1,2},
	{2,0,1,2},
	{2,0,1,1},
	{2,1,0,1},
	{2,1,0,2},
	{2,0,0,0} };

	vector<int>kind{ 0,0,1,1,0,0,0,1,1,1,1,1,1,1,0 };
	vector<string>name(4);
	name[0] = "����";
	name[1] = "����";
	name[2] = "����";
	name[3] = "�Ŵ�";
	FeatureSelect mySelect(data, kind,name);
	mySelect.Statistics();
	cout << "H(D)=" << endl;
	cout << mySelect.empirical_entropy << endl;
	for (int i = 0;i != 4;i++)
	{
		cout << name[i]<<"g(D,A" << i << ")=" << endl;
		cout << mySelect.gain[i] << endl;
	}
	cout << "Lets creat Tree" << endl;
	DecisionTree myTree(data, kind, name);
	myTree.root = myTree.Creat(data, kind, name);
	myTree.PrintTree(myTree.root,0);

	system("pause");
	waitKey();
	return 0;
}