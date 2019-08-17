#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <bitset>

using namespace std;

struct Point{
	int n;
	Point(int _n) : n(_n) {
		cout<<"New point "<<n<<endl;
	}
};

struct Edge{
	Point &p1, &p2;
	int capacity;
	
	Edge(Point &_p1, Point &_p2, int _capacity) : p1(_p1), p2(_p2), capacity(_capacity) {
		cout<<"New edge ("<<_p1.n<<", "<<_p2.n<<") with c="<<_capacity<<endl;
	}

};

struct Graph{
	vector<Edge>edges;
	vector<Point>points;

	Point &getPoint(int n){
		for(auto p: points){
			if( p.n == n ){
				return *(&p);
			}
		}
		throw std::runtime_error("No point with this number");
	}

	bool isUnique(int n){
		for(auto p: points){
			if( p.n == n ){
				return false;
			}
		}
		return true;
	}

	void addPoint(int n){
		if( !isUnique(n) ){
			throw std::runtime_error("Not unique point number");
		}
		points.push_back(*(new Point(n)));
	}

	void addEdge(int n1, int n2, int capacity){
		edges.push_back(*(new Edge(getPoint(n1), getPoint(n2), capacity)));
	}

	virtual ~Graph(){
		for(auto p: points){
			delete &p;
		}
		
		for(auto e: edges){
			delete &e;
		}
	}

	int getPointCount(){
		return points.size;
	}
};

struct Division{
	vector<Point *>S;
	
	Division(Graph &g, Point &s, bitset &bs){
		S.push_back(&s);
		int cnt = g.getPointCount();
		for(int i=1; i < cnt-1; ++i){ 
			if( bs.test(i) ){
				S.push_back( &(g.getPoint(i)) );
			}
		}
	}
	
	bool isS(Point &p){
		for(auto sp: S){
			if( sp == &p ){
				return true;
			}
		}
		return false;
	}

	
};

int main(){
	Graph g;
	
	for(int i=0; i<12; ++i){
		g.addPoint(i);
	}

	g.addEdge(0, 1, 240);
	g.addEdge(0, 2, 330);
	g.addEdge(0, 3, 170);
	g.addEdge(0, 4, 190);
	g.addEdge(0, 5, 250);
	g.addEdge(1, 7, 130);
	g.addEdge(1, 8, 120);
	g.addEdge(1, 9, 70);
	g.addEdge(2, 9, 200);
	g.addEdge(2, 10, 230);
	g.addEdge(3, 6, 80);
	g.addEdge(3, 10, 160);
	g.addEdge(4, 6, 110);
	g.addEdge(4, 10, 130);
	g.addEdge(5, 7, 200);
	g.addEdge(5, 8, 90);
	g.addEdge(6, 11, 150);
	g.addEdge(7, 11, 240);
	g.addEdge(8, 11, 140);
	g.addEdge(9, 11, 190);
	g.addEdge(10, 11, 460);
	
		
	
	
	return 0;
} 
