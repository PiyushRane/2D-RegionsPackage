#include <bits/stdc++.h>
using namespace std;
double min1 = pow(10,-6);

class point{
public:
	double x;
	double y;
};

class region{
public:
	point origin;

	virtual double contains(point p){}
	virtual void translate(point *p){}
	virtual void rotate(point *p){}
	// virtual void rotate(double angle){

	// }

};

class basic: public region{};
// public:
// 	// region *r;

// 	double contains(point p){
// 		cout << "point in basic";
// 	}

// 	// void translate(double x,double y){
// 	// 	origin.x += x;
// 	// 	origin.y += y; 
// 	// }
// 	// void rotate(double angle){

// 	// }
// };

class Union: public region{
public:
	region *r1, *r2;

	double contains(point p){
		// cout << "point in Union";
		if(r1->contains(p) || r2->contains(p))
			return true;
		else return false;
	}
};

class intersection: public region{
public:
	region *r1, *r2;

	double contains(point p){
		// cout << "point in intersection";
		if(r1->contains(p) && r2->contains(p))
			return true;
		else return false;
	}
};

class complement: public region{
public:
	region *r;
	double contains(point p){
		// cout << "point in complement";
		if(r->contains(p))
			return false;
		else return true;
	}
};

class circle: public basic{
public:
	point centre;
	double rad;
	void setOrigin(){
		origin = centre;
		cout << "origin: ("<< origin.x << ", " << origin.y << ")" << endl;
	}
	// origin = centre;
	double contains(point p){
	if (pow((p.x - origin.x),2) + pow((p.y - origin.y),2) <= pow(rad,2)){
        return true;  
	}
    else{
    		return false;
    	}
	}

	void translate(double x, double y){

	}
};

class triangle: public basic{
public:
	point a, b, c;
	double area(point a,point b, point c){
		return abs(((a.x*(b.y-c.y)) + (b.x*(c.y-a.y)) + (c.x*(a.y-b.y)))/2.0);
	}
	void setOrigin(){
		origin.x = (a.x+b.x+c.x)/3;
		origin.y = (a.y+b.y+c.y)/3;
		cout << "origin: ("<< origin.x << ", " << origin.y << ")" << endl;
	}
	double contains(point p){
		double A = area(a,b,c);
		double A1 = area(p,b,c);
		double A2 = area(a,p,c);
		double A3 = area(a,b,p);
		if(abs(A - (A1+A2+A3)) < min1){
	        return true;
		}else {
			// cout << A << A1+A2+A3 <<"\n";
        				return false;
		}
	}
};

class rectangle: public basic{
public:
	point a, b, c, d; // consider in this order only

	void setOrigin(){
		origin.x = (a.x+b.x+c.x+d.x)/4;
		origin.y = (a.y+b.y+c.y+d.y)/4;
		cout << "origin: ("<< origin.x << ", " << origin.y << ")" << endl;
	}

	double contains(point p){
		triangle A01, A02, a1, a2, a3, a4;
		double A = A01.area(a,b,c) + A02.area(a,d,c);
		double A1 = a1.area(p,a,b);
		double A2 = a2.area(p,b,c);
		double A3 = a3.area(p,c,d);
		double A4 = a4.area(p,a,d);
		if(abs(A - (A1+A2+A3+A4)) < min1){
        				return true;
		}
		else{
        				return false;	
		} 
	}
};

class square: public rectangle{};

class annulus: public region{
public:
	circle c1, c2;     //c1 and c2 have same centre

	void setOrigin(){
		if(c1.centre.x != c2.centre.x && c1.centre.y != c2.centre.y){
			cout << "both circles do not have same centre" << endl;
		} else {
			origin = c1.centre;
			cout << "origin of annulus: ("<< origin.x << ", " << origin.y << ")" << endl;
		}
		

	}
	double contains(point p){

		if(c1.rad > c2.rad){
			if(c1.contains(p) && c2.contains(p) == 0)
				return true;
			else return false;
		}
		else {
			if(c1.contains(p) == 0 && c2.contains(p))
				return true;
			else return false;
		}
	}
};

class l_shape: public region{
public:
	rectangle r1, r2;

	void setOrigin(){
		origin.x = (r1.origin.x + r2.origin.x)/2.0 ;
		origin.y = (r1.origin.y + r2.origin.y)/2.0 ;
		cout << "origin: ("<< origin.x << ", " << origin.y << ")" << endl;

	}
	double contains(point p){
		// cout << "point in Union";
		if(r1.contains(p) || r2.contains(p))
			return true;
		else return false;
	}
};

class translatedPoint: public region{
public:
	region *r;
	double x,y;
	// r.origin.x += x;
	// r.origin.y += y;

	void translate(point *p){
		p->x += x ;//- (r->origin.x);
		p->y += y ;//- (r->origin.y);
		cout << "translated: " << x << "," << y << endl;
	}
};

class rotatedPoint: public region{
public:
	region *r;
	double angle;

	void rotate(point *p){
		double tempx = p->x;
		double tempy = p->y;

		// p->x = (tempx - r->origin.x) * cos((M_PI * angle) / 180) - (tempy - r->origin.y) * sin((M_PI * angle) / 180);
		// p->y = (tempy - r->origin.y) * cos((M_PI * angle / 180)) + (tempx - r->origin.x) * sin((M_PI * angle) / 180);
		p->x = (tempx - r->origin.x) * cos(angle) - (tempy - r->origin.y) * sin(angle) ;
		p->y = (tempy - r->origin.y) * cos(angle) + (tempx - r->origin.x) * sin(angle) ;

		p->x = p->x + r->origin.x;
		p->y = p->y + r->origin.y;
		cout << "rotated angle: " << angle << " radians" << endl;
		cout << "rotated point: (" << p->x << " ," << p->y << ")" << endl;
	}
};

void CIRCLE(){
	cout << endl;
	point A = {2,3}, B = {10,10};
	circle c,c1,c2;
	c.centre = {4,4};
	c.rad = 5;
	c.setOrigin();

	if(c.contains(A)){
		cout << "circle contains point (" << A.x << ", " << A.y << ")" << endl;
	}else {
        	cout << "point (" << A.x << ", " << A.y << ")" << " is not in circle" << endl;
	}
	if(c.contains(B)){
		cout << "circle contains point (" << B.x << ", " << B.y << ")" << endl;
	}else {
        	cout << "point (" << B.x << ", " << B.y << ")" << " is not in circle" << endl;
	}

	// translated circle
	cout << "<------------- translated ------------>>" << endl; 
	
	c1 = c;
	translatedPoint tr;
	tr.r = &c1;
	tr.x = 1, tr.y = 2;
	tr.translate(&c1.centre);
	c1.setOrigin();
	
	point A1 = {1,1}, B1 = {5,10};

	if(c.contains(A1)){
		cout << "circle contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in circle" << endl;
	}
	if(c1.contains(A1)){
		cout << "circle contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in circle" << endl;
	}
	if(c.contains(B1)){
		cout << "circle contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in circle" << endl;
	}
	if(c1.contains(B1)){
		cout << "circle contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in circle" << endl;
	}

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 

	c2 = c;
	rotatedPoint rp;
	rp.r = &c2;
	rp.angle = M_PI/2.0;
	rp.rotate(&c2.centre);
	c2.setOrigin();

	point A2 = {1,1}, B2 = {5,10};   //this case of A2,B2 is not applicable for circle
	if(c.contains(A2)){
		cout << "circle contains point (" << A2.x << ", " << A2.y << ")" << endl;
	}else {
        	cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in circle" << endl;
	}
	if(c2.contains(A2)){
		cout << "circle contains point (" << A2.x << ", " << A2.y << ")" << endl;
	}else {
        	cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in circle" << endl;
	}
	if(c.contains(B2)){
		cout << "circle contains point (" << B2.x << ", " << B2.y << ")" << endl;
	}else {
        	cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in circle" << endl;
	}
	if(c2.contains(B2)){
		cout << "circle contains point (" << B2.x << ", " << B2.y << ")" << endl;
	}else {
        	cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in circle" << endl;
	}
	cout << endl;
}

void TRIANGLE(){
	cout << endl;
	point A = {3,1},B = {2,7};
	triangle t,t1,t2;
	t.a = {2,0}, t.b = {5,0}, t.c = {2,6};
	t.setOrigin();

	if(t.contains(A)) cout << "triangle contains point (" << A.x << ", " << A.y << ")" << endl;
		else cout << "point (" << A.x << ", " << A.y << ")" << " is not in triangle" << endl;
	if(t.contains(B)) cout << "triangle contains point (" << B.x << ", " << B.y << ")" << endl;
		else cout << "point (" << B.x << ", " << B.y << ")" << " is not in triangle" << endl;	

	//translated
	cout << "<------------- translated ------------>>" << endl; 
	
	t1 = t;
	translatedPoint tr;
	tr.r = &t1;
	tr.x = -2, tr.y = 0;
	tr.translate(&t1.a);
	tr.translate(&t1.b);
	tr.translate(&t1.c);
	t1.setOrigin();
	
	point A1 = {3,1}, B1 = {1,1};
	if(t.contains(A1)) cout << "triangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in triangle" << endl;
	if(t1.contains(A1)) cout << "triangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in triangle" << endl;
	if(t.contains(B1)) cout << "triangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in triangle" << endl;
	if(t1.contains(B1)) cout << "triangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in triangle" << endl;

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 

	t2 = t;
	rotatedPoint rp;
	rp.r = &t2;
	rp.angle = M_PI/2.0;
	rp.rotate(&t2.a);
	rp.rotate(&t2.b);
	rp.rotate(&t2.c);
	t2.setOrigin();


	point A2 = {2,3}, B2 = {4,3}; 
	if(t.contains(A2)) cout << "triangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in triangle" << endl;
	if(t2.contains(A2)) cout << "triangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in triangle" << endl;
	if(t.contains(B2)) cout << "triangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in triangle" << endl;
	if(t2.contains(B2)) cout << "triangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in triangle" << endl;
	cout << endl;
}

void RECTANGLE(){
	cout << endl;
	point A = {6,3},B = {2,7};
	rectangle r,r1,r2;
	r.a = {4,1}, r.b = {8,1}, r.c = {8,7}, r.d = {4,7};
	r.setOrigin();
	if(r.contains(A)) cout << "rectangle contains point (" << A.x << ", " << A.y << ")" << endl;
		else cout << "point (" << A.x << ", " << A.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B)) cout << "rectangle contains point (" << B.x << ", " << B.y << ")" << endl;
		else cout << "point (" << B.x << ", " << B.y << ")" << " is not in rectangle" << endl;	

	//translated
	cout << "<------------- translated ------------>>" << endl; 
	
	r1 = r;
	translatedPoint tr;
	tr.r = &r1;
	tr.x = 2, tr.y = 3;
	tr.translate(&r1.a);
	tr.translate(&r1.b);
	tr.translate(&r1.c);
	tr.translate(&r1.d);
	r1.setOrigin();
	
	point A1 = {5,3}, B1 = {9,8};

	if(r.contains(A1)) cout << "rectangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in rectangle" << endl;	
	if(r1.contains(A1)) cout << "rectangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B1)) cout << "rectangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in rectangle" << endl;	
	if(r1.contains(B1)) cout << "rectangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in rectangle" << endl;

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 

	r2 = r;
	rotatedPoint rp;
	rp.r = &r2;
	rp.angle = M_PI/2.0;
	rp.rotate(&r2.a);
	rp.rotate(&r2.b);
	rp.rotate(&r2.c);
	rp.rotate(&r2.d);
	r2.setOrigin();


	point A2 = {5.2,6.2}, B2 = {3.5,4.5};   

	if(r.contains(A2)) cout << "rectangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in rectangle" << endl;	
	if(r2.contains(A2)) cout << "rectangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B2)) cout << "rectangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in rectangle" << endl;	
	if(r2.contains(B2)) cout << "rectangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in rectangle" << endl ;
		cout << endl;
}
void SQUARE(){
	cout << endl;
	point A = {1,2},B = {2,7};
	rectangle r,r1,r2;
	r.a = {4,0}, r.b = {0,4}, r.c = {-4,0}, r.d = {0,-4};
	r.setOrigin();
	if(r.contains(A)) cout << "rectangle contains point (" << A.x << ", " << A.y << ")" << endl;
		else cout << "point (" << A.x << ", " << A.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B)) cout << "rectangle contains point (" << B.x << ", " << B.y << ")" << endl;
		else cout << "point (" << B.x << ", " << B.y << ")" << " is not in rectangle" << endl;	

	//translated
	cout << "<------------- translated ------------>>" << endl; 
	
	r1 = r;
	translatedPoint tr;
	tr.r = &r1;
	tr.x = -1, tr.y = 2;
	tr.translate(&r1.a);
	tr.translate(&r1.b);
	tr.translate(&r1.c);
	tr.translate(&r1.d);
	r1.setOrigin();
	
	point A1 = {1,-1}, B1 = {2.2,2.2};

	if(r.contains(A1)) cout << "rectangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in rectangle" << endl;	
	if(r1.contains(A1)) cout << "rectangle contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B1)) cout << "rectangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in rectangle" << endl;	
	if(r1.contains(B1)) cout << "rectangle contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in rectangle" << endl;

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 

	r2 = r;
	rotatedPoint rp;
	rp.r = &r2;
	rp.angle = M_PI/4.0;
	rp.rotate(&r2.a);
	rp.rotate(&r2.b);
	rp.rotate(&r2.c);
	rp.rotate(&r2.d);
	r2.setOrigin();


	point A2 = {0.4,3}, B2 = {2.4,2};   

	if(r.contains(A2)) cout << "rectangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in rectangle" << endl;	
	if(r2.contains(A2)) cout << "rectangle contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in rectangle" << endl;	
	if(r.contains(B2)) cout << "rectangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in rectangle" << endl;	
	if(r2.contains(B2)) cout << "rectangle contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in rectangle" << endl ;
	cout << endl;
}

void COMPLIMENT(){
	cout << endl;
	point A = {2,3}, B = {10,10};
	circle c,c1;
	complement com,com1;
	com.r = &c;
	c.centre = {4,4};
	c.rad = 5;
	c.setOrigin();
	if(com.contains(A)) cout << "compliment contains point (" << A.x << ", " << A.y << ")" << endl;
		else cout << "point (" << A.x << ", " << A.y << ")" << " is not in compliment" << endl;	
	if(com.contains(B)) cout << "compliment contains point (" << B.x << ", " << B.y << ")" << endl;
		else cout << "point (" << B.x << ", " << B.y << ")" << " is not in compliment" << endl;	

	// translated circle
	cout << "<------------- translated ------------>>" << endl; 
	
	c1 = c;
	translatedPoint tr;
	tr.r = &c1;
	tr.x = 1, tr.y = 2;
	tr.translate(&c1.centre);
	c1.setOrigin();
	com1.r = &c1;
	
	point A1 = {1,1}, B1 = {5,10};
	if(com.contains(A1)){
		cout << "circle contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in circle" << endl;
	}
	if(com1.contains(A1)){
		cout << "circle contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in circle" << endl;
	}
	if(com.contains(B1)){
		cout << "circle contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in circle" << endl;
	}
	if(com1.contains(B1)){
		cout << "circle contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in circle" << endl;
	}

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 
	cout << "no sense of rotation of compliment of circle." << endl; 
	cout << endl;
}

void ANNULUS(){
	cout << endl;
	point A = {7,4}, B = {10,10};
	circle c1,c2;
	c1.centre = {4,4};
	c1.rad = 5;
	c1.setOrigin();
	c2.centre = {4,4};
	c2.rad = 2;
	c2.setOrigin();
	annulus anu,anu1,anu2;
	anu.c1 = c1, anu.c2 = c2;
	anu.setOrigin();

	if(anu.contains(A)){
		cout << "annulus contains point (" << A.x << ", " << A.y << ")" << endl;
	}else {
        	cout << "point (" << A.x << ", " << A.y << ")" << " is not in annulus" << endl;
	}
	if(anu.contains(B)){
		cout << "annulus contains point (" << B.x << ", " << B.y << ")" << endl;
	}else {
        	cout << "point (" << B.x << ", " << B.y << ")" << " is not in annulus" << endl;
	}

	// translated circle
	cout << "<------------- translated ------------>>" << endl; 
	
	anu1 = anu;
	translatedPoint tr;
	tr.r = &anu1;
	tr.x = 1, tr.y = 2;
	tr.translate(&anu1.c1.centre);
	tr.translate(&anu1.c2.centre);
	anu1.c1.setOrigin();
	anu1.c1.setOrigin();
	anu1.setOrigin();
	// cout << anu1.c1.rad << anu1.c2.rad;
	// cout << "hi";
	point A1 = {1,1}, B1 = {5,10};

	if(anu.contains(A1)){
		cout << "annulus contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in annulus" << endl;
	}
	if(anu1.contains(A1)){
		cout << "annulus contains point (" << A1.x << ", " << A1.y << ")" << endl;
	}else {
        	cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in annulus" << endl;
	}
	if(anu.contains(B1)){
		cout << "annulus contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in annulus" << endl;
	}
	if(anu1.contains(B1)){
		cout << "annulus contains point (" << B1.x << ", " << B1.y << ")" << endl;
	}else {
        	cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in annulus" << endl;
	}

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 
	cout << "no sense of rotation of compliment of circle." << endl;
	cout << endl; 
}

void L_SHAPE(){
	cout << endl;
	point A = {6,3},B = {2,7};
	rectangle r1,r2;
	r1.a = {4,0}, r1.b = {8,0}, r1.c = {8,7}, r1.d = {4,7};
	r1.setOrigin();
	r2.a = {4,0}, r2.b = {12,0}, r2.c = {12,4}, r2.d = {4,4};
	r2.setOrigin();
	l_shape l,l1,l2;
	l.r1 = r1, l.r2 = r2;
	l.setOrigin();

	if(l.contains(A)) cout << "L_SHAPE contains point (" << A.x << ", " << A.y << ")" << endl;
		else cout << "point (" << A.x << ", " << A.y << ")" << " is not in L_SHAPE" << endl;	
	if(l.contains(B)) cout << "L_SHAPE contains point (" << B.x << ", " << B.y << ")" << endl;
		else cout << "point (" << B.x << ", " << B.y << ")" << " is not in L_SHAPE" << endl;	

	//translated
	cout << "<------------- translated ------------>>" << endl; 
	
	l1 = l;
	translatedPoint tr;
	tr.r = &l1;
	tr.x = 2, tr.y = 0;
	tr.translate(&l1.r1.a);
	tr.translate(&l1.r1.b);
	tr.translate(&l1.r1.c);
	tr.translate(&l1.r1.d);
	tr.translate(&l1.r2.a);
	tr.translate(&l1.r2.b);
	tr.translate(&l1.r2.c);
	tr.translate(&l1.r2.d);
	l1.r1.setOrigin();
	l1.r2.setOrigin();
	l1.setOrigin();
	
	point A1 = {5,3}, B1 = {13,2};

	if(l.contains(A1)) cout << "L_SHAPE contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in L_SHAPE" << endl;	
	if(l1.contains(A1)) cout << "L_SHAPE contains point (" << A1.x << ", " << A1.y << ")" << endl;
		else cout << "point (" << A1.x << ", " << A1.y << ")" << " is not in L_SHAPE" << endl;	
	if(l.contains(B1)) cout << "L_SHAPE contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in L_SHAPE" << endl;	
	if(l1.contains(B1)) cout << "L_SHAPE contains point (" << B1.x << ", " << B1.y << ")" << endl;
		else cout << "point (" << B1.x << ", " << B1.y << ")" << " is not in L_SHAPE" << endl;

	//rotated region
	cout << "<------------- rotated ------------>>" << endl; 

	l2 = l;
	rotatedPoint rp;
	rp.r = &l2;
	rp.angle = M_PI/2.0;
	rp.rotate(&l2.r1.a);
	rp.rotate(&l2.r1.b);
	rp.rotate(&l2.r1.c);
	rp.rotate(&l2.r1.d);
	rp.rotate(&l2.r2.a);
	rp.rotate(&l2.r2.b);
	rp.rotate(&l2.r2.c);
	rp.rotate(&l2.r2.d);
	l1.r1.setOrigin();
	l1.r2.setOrigin();
	l1.setOrigin();


	point A2 = {5.2,6.2}, B2 = {9,5};   

	if(l.contains(A2)) cout << "L_SHAPE contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in rL_SHAPE" << endl;	
	if(l2.contains(A2)) cout << "L_SHAPE contains point (" << A2.x << ", " << A2.y << ")" << endl;
		else cout << "point (" << A2.x << ", " << A2.y << ")" << " is not in L_SHAPE" << endl;	
	if(l.contains(B2)) cout << "L_SHAPE contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in L_SHAPE" << endl;	
	if(l2.contains(B2)) cout << "L_SHAPE contains point (" << B2.x << ", " << B2.y << ")" << endl;
		else cout << "point (" << B2.x << ", " << B2.y << ")" << " is not in L_SHAPE" << endl ;
		cout << endl;
}

int main(){

	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
	#endif    
// comment and check each one by one
CIRCLE();
TRIANGLE();	
RECTANGLE();
SQUARE();
COMPLIMENT();
ANNULUS();
L_SHAPE();


	return 0;
}