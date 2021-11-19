#include <iostream>
using namespace std;

int main(){

	int n; //number of point loads
	float a; //distance between support A and left end of the beam
	float b; //distance between support B and right end of the beam
	float l; //span of the beam
	float s; //section modulus of the beam
    
    cout<<"INPUT :"<<endl;
    cout<<endl;

	cout<<"Enter the number of point loads :";
	cin>>n;
	cout<<endl;

	cout<<"Distance between support A and left end of the beam [in mm] :";
	cin>>a;
	cout<<endl;

	cout<<"Distance between support B and right end of the beam [in mm] :";
	cin>>b;
	cout<<endl;

	cout<<"Span of the beam [in mm] :";
	cin>>l;
	cout<<endl;

	cout<<"Section modulus of the beam [in mm^3] :";
	cin>>s;
	cout<<endl;


	float loads[n]; // array to store the value of each load
	float dist_of_loads[n]; // array to store the distance of each load from left end

	

	float sumP=0; //summation of all loads
	float reactionB=0; //reaction forceat end A
	float reactionA=0; //reaction force at end B

	for(int i=1;i<=n;i++){

		cout<<"Enter the point load p"<<i<<" [in N] :";
		cin>>loads[i];

		cout<<"Enter the distance x"<<i<<" of load p"<<i<<" from left end [in mm] :";
		cin>>dist_of_loads[i];

		cout<<endl;

		sumP=sumP+ loads[i];
		reactionB=reactionB + (loads[i]*(dist_of_loads[i]-a))/l;


	}

	reactionA=sumP-reactionB;

	int m; // number of cross sections at which stress is to be found

	cout<<"Enter the number of Cross Sections at which stress is to be found :";
	cin>>m;
	cout<<endl;

	float dist[m]; //array of distances of cross sections at which stress is to be calculated

	for(int j=1;j<=m;j++){

		cout<<"Enter the distance of Cross section "<<j<<" [in mm] :";
		cin>>dist[j];
		cout<<endl;
	}

	cout<<"OUTPUT :"<<endl;
    cout<<endl;
    cout<<"Reaction force at A [in kN] :"<<reactionA/1000<<endl;
	cout<<"Reaction force at b [in kN] :"<<reactionB/1000<<endl;
	cout<<endl;

	for(int k=1;k<=m;k++){

		float c=0,d=0;
		int stepA,stepB,stepI;

		if(dist[k]>=a){
			stepA=1;
		}
		else
			stepA=0;


		if(dist[k]>=a+l){
			stepB=1;
		}
		else
			stepB=0;


		float V; //shear stress
		float M; // bending moment
		float sigma; // normal stress

		for(int i=1;i<=n;i++){

			if(dist[k]>=dist_of_loads[i]){

				stepI=1;
			}
			else
				stepI=0;


			c=c+loads[i]*stepI;
			d=d+loads[i]*(dist[k]-dist_of_loads[i])*stepI;

			

			V=reactionA*stepA + reactionB*stepB -c;
			M=reactionA*(dist[k]-a)*stepA +reactionB*(dist[k]-a-l)*stepB - d;
			sigma=M/s;

			if(dist[k]>l){
				V=M=sigma=0;
			}
		}


		
		cout<<"At x="<<dist[k]/1000<<" m :"<<endl;
		cout<<"(1) Shear Stress [in kN] :"<<V/1000<<endl;
		cout<<"(2) Bending Moment [in kN-m] :"<<M/1000000<<endl;
		cout<<"(3) Normal Stress [in MPa] :"<<sigma<<endl;
		
		cout<<endl; 



	}

	


}