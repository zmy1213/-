#include<iostream>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<climits>
#include<cmath>
using namespace std;
class Node;
class Edge;

class Node
{
public:
	int value;
	int in;
	int out;
	vector<Node>* nexts;
	vector<Edge>* edges;
	Node(int in =0,int out=0,int value = 0)
	{
		this->value = value;
		this->in = in;
		this->out = out;
		nexts = new vector<Node>();
		edges = new vector<Edge>();
	}
};
class Edge
{
public:
	int weight;
	Node from;
	Node to;
	Edge(int weight, Node from, Node to)
	{
		this->weight = weight;
		this->from = from;
		this->to = to;
	}
};
class Compare_Edge
{
public:
	bool operator()(const Edge& e1, const Edge& e2)const
	{
		return e1.weight < e2.weight;
	}
};
class Compare_Edge1
{
public:
	bool operator()(const Edge& e1, const Edge& e2)const
	{
		return e1.weight > e2.weight;
	}
};
class Compare_Node
{
public:
	bool operator()(const Node& n1, const Node& n2)const
	{
		return n1.value < n2.value;
	}
};
class Graph
{
public:
	map<int, Node>nodes;
	set<Edge, Compare_Edge>edges;
};
void bfs(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	queue<Node>qu;
	set<Node, Compare_Node>s;

	qu.push(*root);
	s.insert(*root);

	while (!qu.empty())
	{
		Node cur = qu.front();
		qu.pop();

		Node next;
		cout << cur.value << endl;
		for (vector<Node>::iterator it = cur.nexts->begin(); it != cur.nexts->end(); it++)
		{
			next = *it;
			if (!s.count(next))
			{
				s.insert(next);
				qu.push(next);
			}
		}
	}
}
void dfs(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	stack<Node> sta;
	set<Node, Compare_Node> se;

	cout << root->value << endl;
	sta.push(*root);
	se.insert(*root);
	while (!sta.empty())
	{
		Node cur = sta.top();
		sta.pop();
		Node next;
		for (vector<Node>::iterator it = cur.nexts->begin(); it != cur.nexts->end(); it++)
		{
			next = *it;
			if (!se.count(next))
			{
				sta.push(cur);
				sta.push(next);
				se.insert(next);
				cout << next.value << endl;
				break;
			}
		}
	}
}
//拓扑排序
vector<Node> sortedToplogy(Graph &g)
{
	map<Node,int,Compare_Node>inMap;
	queue<Node> zeroInQueue;
	
	for (map<int,Node>::iterator it =g.nodes.begin();it!=g.nodes.end();it++)
	{
		inMap.insert(map<Node, int>::value_type(it->second, it->second.in));
		if (it->second.in==0)
		{
			zeroInQueue.push(it->second);
		}
	}
	//拓扑排序的结果，依次加入result
	vector<Node> result;
	while (!zeroInQueue.empty())
	{
		Node cur = zeroInQueue.front();
		zeroInQueue.pop();
		result.push_back(cur);
		Node next;
		for (vector<Node>::iterator it = cur.nexts->begin(); it != cur.nexts->end(); it++)
		{
			next = *it;
			next.in -= 1;

			inMap.at(next) -= 1;
			if (inMap.at(next)==0)
			{
				zeroInQueue.push(next);
			}
		}
	}
	return result;
}
void Init1(Graph& g)
{
	Node n1(0,0,1);
	Node n2(0,0,2);
	Node n3(0,0,3);
	Node n4(0,0,4);


	n1.nexts->push_back(n2);
	n2.nexts->push_back(n3);
	n2.nexts->push_back(n4);
	n3.nexts->push_back(n1);

	g.nodes.insert(map<int, Node>::value_type(1, n1));
	g.nodes.insert(map<int, Node>::value_type(2, n2));
	g.nodes.insert(map<int, Node>::value_type(3, n3));
	g.nodes.insert(map<int, Node>::value_type(4, n4));


	Edge e1(1, n1, n2);
	Edge e2(2, n2, n3);
	Edge e3(3, n2, n4);
	Edge e4(4, n3, n1);

	g.edges.insert(e1);
	g.edges.insert(e2);
	g.edges.insert(e3);
	g.edges.insert(e4);

	n1.edges->push_back(e1);
	n2.edges->push_back(e2);
	n2.edges->push_back(e3);
	n3.edges->push_back(e4);

}
void Init2(Graph& g)
{
	Node a(0,2,1);
	Node b(1,2,2);
	Node c(2,1,3);
	Node d(2,0,4);

	a.nexts->push_back(b);
	a.nexts->push_back(c);
	b.nexts->push_back(c);
	b.nexts->push_back(d);
	c.nexts->push_back(d);

	g.nodes.insert(map<int, Node>::value_type(1,a));
	g.nodes.insert(map<int, Node>::value_type(2,b));
	g.nodes.insert(map<int, Node>::value_type(3,c));
	g.nodes.insert(map<int, Node>::value_type(4,d));
}
void Init3(Graph& g)
{
	Node a(0, 0, 1);
	Node b(0, 0, 2);
	Node c(0, 0, 3);
	Node d(0, 0, 4);
	Node e(0, 0, 5);

	a.nexts->push_back(b);
	a.nexts->push_back(c);
	a.nexts->push_back(d);

	b.nexts->push_back(a);
	b.nexts->push_back(d);
	b.nexts->push_back(e);

	c.nexts->push_back(a);
	c.nexts->push_back(d);

	d.nexts->push_back(c);
	d.nexts->push_back(a);
	d.nexts->push_back(b);

	e.nexts->push_back(b);

	g.nodes.insert(map<int, Node>::value_type(1, a));
	g.nodes.insert(map<int, Node>::value_type(2, b));
	g.nodes.insert(map<int, Node>::value_type(3, c));
	g.nodes.insert(map<int, Node>::value_type(4, d));
	g.nodes.insert(map<int, Node>::value_type(5, e));

	Edge e1(7, a, b);
	Edge e3(2, a, c);
	Edge e5(4, c, d);
	Edge e7(1000, b, d);
	Edge e9(100, d, a);
	Edge e11(10000, b, e);

	g.edges.insert(e1);
	g.edges.insert(e3);
	g.edges.insert(e5);
	g.edges.insert(e7);
	g.edges.insert(e9);
	g.edges.insert(e11);
}
void Init4(Graph& g)
{
	Node a(0,0,1);
	Node b(0,0,2);
	Node c(0,0,3);
	Node d(0,0,4);
	Node e(0,0,5);
	Node f(0, 0, 6);

	Edge ab(6, a, b);
	Edge ba(6, b, a);
	Edge ad(5, a, d);
	Edge da(5, d, a);
	Edge ac(1, a, c);
	Edge ca(1, c, a);
	Edge bc(5, b, c);
	Edge cb(5, c, b);
	Edge cd(5, c, d);
	Edge dc(5, d, c);
	Edge be(3, b, e);
	Edge eb(3, e, b);
	Edge ce(6, c, e);
	Edge ec(6, e, c);
	Edge cf(4, c, f);
	Edge fc(4, f, c);
	Edge ef(6, e, f);
	Edge fe(6, f, e);
	Edge df(2, d, f);
	Edge fd(2, f, d);

	a.nexts->push_back(b);
	a.nexts->push_back(c);
	a.nexts->push_back(d);
	a.edges->push_back(ab);
	a.edges->push_back(ac);
	a.edges->push_back(ad);

	b.nexts->push_back(a);
	b.nexts->push_back(c);
	b.nexts->push_back(e);
	b.edges->push_back(ba);
	b.edges->push_back(bc);
	b.edges->push_back(be);

	c.nexts->push_back(a);
	c.nexts->push_back(b);
	c.nexts->push_back(d);
	c.nexts->push_back(e);
	c.nexts->push_back(f);
	c.edges->push_back(ca);
	c.edges->push_back(cb);
	c.edges->push_back(cd);
	c.edges->push_back(ce);
	c.edges->push_back(cf);

	d.nexts->push_back(a);
	d.nexts->push_back(c);
	d.nexts->push_back(f);
	d.edges->push_back(da);
	d.edges->push_back(df);
	d.edges->push_back(dc);

	e.nexts->push_back(b);
	e.nexts->push_back(c);
	e.nexts->push_back(f);
	e.edges->push_back(eb);
	e.edges->push_back(ec);
	e.edges->push_back(ef);

	f.nexts->push_back(c);
	f.nexts->push_back(e);
	f.nexts->push_back(d);
	f.edges->push_back(fe);
	f.edges->push_back(fc);
	f.edges->push_back(fd);

	g.nodes.insert(map<int, Node>::value_type(1, a));
	g.nodes.insert(map<int, Node>::value_type(2, b));
	g.nodes.insert(map<int, Node>::value_type(3, c));
	g.nodes.insert(map<int, Node>::value_type(4, d));
	g.nodes.insert(map<int, Node>::value_type(5, e));
	g.nodes.insert(map<int, Node>::value_type(6, f));
}
void Print_Vector(vector<Node> v)
{
	for (vector<Node>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->value << " ";
	}
	cout << endl;
}
void Print_Set(set<Edge,Compare_Edge> v)
{
	for (set<Edge,Compare_Edge>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->weight << " ";
	}
	cout << endl;
}
class Mysets
{
public:
	map<Node,vector<Node>*,Compare_Node> setMap;
	Mysets(vector<Node> *nodes);
	bool isSameSet(Node from, Node to);
	void Union(Node from,Node to);
};
Mysets::Mysets(vector<Node> *nodes)
{
	int i = 0;
	for (vector<Node>::iterator it = nodes->begin(); it != nodes->end(); it++)
	{
		i++;
		vector<Node>* set = new vector<Node>();
		cout << "Node"<< i <<": " << set << endl;
		set->push_back(*it);
		setMap.insert(map<Node,vector<Node>*>::value_type(*it,set));
	}
}
bool Mysets::isSameSet(Node from, Node to)
{
	vector<Node> *fromSet = setMap.at(from);
	vector<Node> *toSet =  setMap.at(to);
	cout << "from:" <<  fromSet << " to:" << toSet << endl;
	return (fromSet) == (toSet);
}
void Mysets::Union(Node from, Node to)
{
	vector<Node> *fromSet = setMap.at(from);
	vector<Node> *toSet =setMap.at(to);
	for (vector<Node>::iterator it = toSet->begin(); it != toSet->end(); it++)
	{
		fromSet->push_back(*it);
		setMap.erase(*it);
		setMap.insert(map< Node, vector<Node>*>::value_type(*it,fromSet));
	}
}
set<Edge, Compare_Edge> kruskalMST(Graph &graph)
{
	vector<Node>* nodes = new vector<Node>();
	for (map<int, Node>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++)
	{
		nodes->push_back(it->second);
	}

	Mysets* mysets = new Mysets( nodes);
	priority_queue<Edge,vector<Edge>,Compare_Edge1> qu;

	for (set<Edge>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++)
	{
		qu.push(*it);
	}

	set<Edge,Compare_Edge> result;

	while (!qu.empty())
	{
		Edge edge = qu.top();
		qu.pop();
		if (!mysets->isSameSet(edge.from, edge.to))
		{
			result.insert(edge);
			mysets->Union(edge.from,edge.to);
			edge.to = edge.from;
		}
	}
	return result;
}
set<Edge, Compare_Edge> primMST(Graph &graph)
{
	priority_queue<Edge,vector<Edge>,Compare_Edge1>priorityQueue;
	set<Node, Compare_Node> nodes;
	set<Edge, Compare_Edge> edges;

	for (map<int, Node>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++)
	{
		if (!nodes.count(it->second))
		{
			nodes.insert(it->second);
			for (vector<Edge>::iterator edge = it->second.edges->begin(); edge != it->second.edges->end(); edge++)
			{
				priorityQueue.push(*edge);
			}
			while (!priorityQueue.empty())
			{
				Edge edge = priorityQueue.top();
				priorityQueue.pop();
				Node toNode = edge.to;
				if (!nodes.count(toNode))
				{
					nodes.insert(toNode);
					edges.insert(edge);
					for (vector<Edge>::iterator edge1 = toNode.edges->begin(); edge1 != toNode.edges->end(); edge1++)
					{
						priorityQueue.push(*edge1);
					}
				}
			}
		}
	}
	return edges;
}
Node* getMinDistanceAndUnselectedNode(map<Node, int, Compare_Node> distanceMap, set<Node,Compare_Node>touchedNodes)
{
	Node minNode = NULL;
	int minDistance = INT_MAX;
	for (map<Node, int, Compare_Node>::iterator node = distanceMap.begin(); node != distanceMap.end(); node++)
	{
		Node tem_node = node->first;
		int distance = node->second;
		if (!touchedNodes.count(tem_node) && distance < minDistance)
		{
			minNode = tem_node;
			minDistance = distance;
		}
	}
	Node* result = new Node(minNode);
	return result;
}
map<Node, int, Compare_Node>dijkstra1(Node head)
{
	//从head出发到所有点的最小距离
	//key:到达key点
	//value:最小值
	//没有记录则是正无穷
	map<Node, int, Compare_Node> distanceMap;
	distanceMap.insert(map<Node, int, Compare_Node>::value_type(head, 0));
	set<Node, Compare_Node> selectedNodes;
	Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);

	while (minNode != NULL)
	{
		int distance = distanceMap.at(*minNode);
		for (vector<Edge>::iterator edge = minNode->edges->begin(); edge != minNode->edges->end(); edge++)
		{
			Node toNode = edge->to;
			if (!distanceMap.count(toNode))
			{
				distanceMap.insert(map<Node, int, Compare_Node>::value_type(toNode, distance + edge->weight));
			}
			if (distanceMap.at(toNode) > distance + edge->weight)
			{
				distanceMap.erase(edge->to);
				distanceMap.insert(map<Node, int, Compare_Node>::value_type(edge->to, distanceMap.at(toNode)));
			}
			else
			{
				distanceMap.erase(edge->to);
				distanceMap.insert(map<Node, int, Compare_Node>::value_type(edge->to,distance+edge->weight));
			}
		}
		selectedNodes.insert(*minNode);
		minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
	}
	return distanceMap;
}

int main()
{
	Graph* g = new Graph;
	Init1(*g);
	bfs(&(g->nodes[1]));
	cout << endl;
	dfs(&(g->nodes[1]));
	cout << endl;

	Graph* g1 = new Graph;
	Init2(*g1);
	vector<Node> result = sortedToplogy(*g1);
	Print_Vector(result);
	cout << endl;

	Graph* g2 = new Graph;
	Init3(*g2);
	set<Edge, Compare_Edge>s_re = kruskalMST(*g2);
	Print_Set(s_re);

	Graph* g3 = new Graph;
	Init4(*g3);
	set<Edge, Compare_Edge>s_re1 = primMST(*g3);
	Print_Set(s_re1);

	return 0;
}
