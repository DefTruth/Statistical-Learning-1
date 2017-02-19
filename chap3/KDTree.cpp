#include "KDTree.h"

KDTree::KDTree(int _N)
{
	N = _N;
	root = NULL;
}

KDTree::KDTree()
{
}

KDTree::~KDTree()
{
}

void KDTree::PrintSegment(vector<vector<double>>&segment)
{
	for (auto row : segment)
	{
		for (auto element : row)
		{
			cout << element << " ";
		}
		cout << endl;
	}
}

void KDTree::PrintNode(KnnNode *nowNode)
{
	if (nowNode != NULL)
	{
		nowNode->ShowNode();
		if (nowNode->left_child != NULL)
			PrintNode(nowNode->left_child);
		if (nowNode->right_child != NULL)
			PrintNode(nowNode->right_child);
	}
}


KnnNode *KDTree::Create(vector<vector<double>> &segment, int depth)
{
	//�Ƚ�������jά���Ĵ�С,�Դ�����
	sort(segment.begin(), segment.end(), [capture = make_pair(N, depth)](const vector<double>&a, const vector<double>&b) {
		int j = capture.second%capture.first;
		return a[j] < b[j];
	});
	//PrintSegment(segment);
	int sz = segment.size();
	int mid = sz / 2;
	KnnNode *newNode = new KnnNode;
	newNode->value = segment[mid];
	if (depth == 0)
	{
		root = newNode;
	}
	vector<vector<double>>left_segment, right_segment;
	left_segment.clear();
	right_segment.clear();
	for (int i = 0;i != mid;++i)
		left_segment.push_back(segment[i]);
	for (int i = mid + 1;i != sz;++i)
		right_segment.push_back(segment[i]);
	if (mid)
	{
		newNode->left_child = Create(left_segment, depth + 1);
		newNode->left_child->parent = newNode;
	}
	if (sz - mid - 1)
	{
		newNode->right_child = Create(right_segment, depth + 1);
		newNode->right_child->parent = newNode;
	}
	return newNode;
}

//���ڽ�����,lp�Ǿ���ѡ��,lp=2��ŷʽ����
void KDTree::NearestSearch(int depth, KnnNode *now_node, vector<KnnNode*>&path, const vector<double>&target, KnnNode &now_goal, double &now_distance, bool back, int lp)
{
	//���˽ڵ�ΪҶ�ӣ�����µ�ǰ����㣬���û���ֵback = 1
	if (now_node->left_child == NULL && now_node->right_child == NULL)
	{
		double dis = LpDistance(now_node->value, target, lp);
		if (dis < now_distance)
		{
			now_goal = *now_node;
			now_distance = dis;
		}
		path.push_back(now_node);
		back = 1;
	}
	//�����ǻ��ݣ�����Ŀ����Ƿ�С�ڵ�ǰ�㵱ǰά�ȣ��ǵĻ�������ݹ飬�������ҵݹ�
	if (!back)
	{
		path.push_back(now_node);
		//��ǰά��
		int k = depth%N;
		if(now_node->left_child==NULL)
			NearestSearch(depth + 1, now_node->right_child, path, target, now_goal, now_distance, back, lp);
		else if(now_node->right_child==NULL)
			NearestSearch(depth + 1, now_node->left_child, path, target, now_goal, now_distance, back, lp);
		else if (target[k] < now_node->value[k])
		{
			NearestSearch(depth + 1, now_node->left_child,path,target, now_goal, now_distance, back, lp);
		}
		else
		{
			NearestSearch(depth + 1, now_node->right_child, path, target, now_goal, now_distance, back, lp);
		}
	}
	//���ݼ�鵱ǰ�ڵ㣬����ǰ�綨�����������
	else {
		if (path.size() == 0)
			return;
		KnnNode *next_node = path.back();
		path.pop_back();
		double dis = LpDistance(next_node->value, target, lp);
		if (dis < now_distance)
		{
			now_goal = *next_node;
			now_distance = dis;
		}
		KnnNode *par = next_node->parent;
		//���ֵܽڵ��������ֵܽڵ�ݹ�����
		if (par->left_child != NULL && par->left_child != next_node)
		{
			double other_dis = LpDistance(par->left_child->value, target, lp);
			if (other_dis < now_distance)
			{
				now_goal = *par->left_child;
				now_distance = other_dis;
				back = 0;
				NearestSearch(depth, par->left_child, path, target, now_goal, now_distance, back, lp);
			}
		}
		else if (par->right_child != NULL && par->right_child != next_node)
		{
			double other_dis = LpDistance(par->right_child->value, target, lp);
			if (other_dis < now_distance)
			{
				now_goal = *par->right_child;
				now_distance = other_dis;
				back = 0;
				NearestSearch(depth, par->right_child, path, target, now_goal, now_distance, back, lp);
			}
		}
		else {
			NearestSearch(depth - 1, par, path, target, now_goal, now_distance, back, lp);
		}
		if (path.size() == 0)
			return;
	}
}
