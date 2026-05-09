
#include <stdio.h>
#include <iostream>
#include "Fade_3D.h"
using namespace std;

// Defined in the exampleX files
int example0_main();
int example1_main();

void info()
{
	FADE3D::printLicense();

	cout<<"\n\n\n\tWelcome to the Fade 3D examples"<<endl;
	cout<<"\t-------------------------------"<<endl<<endl;
	cout<<"\t0...HelloTriangulation - a very simple code with visualization"<<endl;
	cout<<"\t1...Benchmark - performance of Fade3D on your computer"<<endl;

}

int main()
{
	info();

	while(true)
	{
		char choice(-1);
		const int NUM_EXAMPLES(2);
		cout << "\n\n\tChoose an example [0-"<<NUM_EXAMPLES-1<<"], q...quit, i...info: ";
		cin>>choice;

		cout<<"\n\n\t-------------------------------------------------"<<endl<<endl;
		switch(choice)
		{
			case '0': example0_main();break;
			case '1': example1_main();break;
			case 'q': return 0;
			case 'i': info();
			default: break;
		}
		cout<<"\n\t-------------------------------------------------"<<endl<<endl;
	}
}

