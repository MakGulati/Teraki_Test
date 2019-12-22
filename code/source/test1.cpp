#include <iostream>
#include <fstream>
#include <vector> 
#include<math.h>
using namespace std;

struct Point3D
    {
    long double x,y,z;

    };

vector<Point3D> pixels,pixelsA,pixelsB,pixelsC;
void removeDupWord(string _str, int _fileNo) 
{   //this function splits lines in words using ' ' delimiter

    vector<long double> input;
    string word = ""; 
    for (auto x : _str) 
    {  
       if (x == ' ') 
       {   
        //    cout << word << endl; 
           input.push_back(stold (word));
           //converts string in long double and pushes it to input vector
           
           word = ""; 
       } 
       else
       { 
           word = word + x; 
       } 
   } 

    long double arr[input.size()];
    copy(input.begin(), input.end(), arr); //copies contents of vector to array
    if (_fileNo==0)
    {
     pixels.push_back({arr[0],arr[1],arr[2]});
     //for pushing to vectors of structure element by element
    }
    if (_fileNo==1)
    {
     pixelsA.push_back({arr[0],arr[1],arr[2]});
    }
    if (_fileNo==2)
    {
     pixelsB.push_back({arr[0],arr[1],arr[2]});
    }
    if (_fileNo==3)
    {
     pixelsC.push_back({arr[0],arr[1],arr[2]});
    }
    input.clear();
 
} 
vector<Point3D> Data_Parsed(int fileNo)
//this function based on fileno. outputs parsed vector of struct
{   string fileName;
    if (fileNo==0)
    {fileName="Car_XYZI_uncompressed_ASCII.ply";
    }
    if (fileNo==1)
    {fileName="Car_XYZI_decompressed_ASCII_A.ply";
    }
    if (fileNo==2)
    {fileName="Car_XYZI_decompressed_ASCII_B.ply";
    }
    if (fileNo==3)
    {fileName="Car_XYZI_decompressed_ASCII_C.ply";
    }
    ifstream inFile;
    pixels.clear(),pixelsA.clear(),pixelsB.clear(),pixelsC.clear();
    // open the file stream
    string input_file_dir="/Users/mayank/Code/Repos/Teraki_Test/input/" ; //TODO:please update file directory based on your computer
    inFile.open(input_file_dir + fileName);
    // check if opening a file failed
    if (inFile.fail()) {
        cerr << "Error opening a file" << endl;
        inFile.close();
        exit(1);
    }
    string line;
    
    int i=0;
    
    while (getline(inFile, line))

    {   i++;
        if (31< i && i< 2141) //coordinates lie in this range of line numbers
        {
            removeDupWord(line,fileNo);
        }
    }
    // close the file stream
    inFile.close();

    vector<Point3D> A;
    if (fileNo==0)
    {A=pixels;
    }
    if (fileNo==1)
    {A=pixelsA;
    }
    if (fileNo==2)
    {A=pixelsB;
    }
    if (fileNo==3)
    {A=pixelsC;
    }

    return (A);
}

//double score_calculator(vector<Point3D> which_pix1, vector<Point3D> which_pix2) {
vector<Point3D>  sorted(vector<Point3D> which_pix1, vector<Point3D> which_pix2) {
    //this function sorts second argument vector w.r.t. first argument vector
    vector<Point3D> _new_pix2;
    _new_pix2.clear();
    int tmp_min;
    vector<int> first;
    first.clear();
    for (int i = 0; i < which_pix1.size(); i++) {
        long double min_dist = 10;                //arbitrary to calculate minimum dist
        for (int j = 0; j < which_pix2.size(); j++) {

            double xs = (which_pix1[i].x - which_pix2[j].x) * (which_pix1[i].x - which_pix2[j].x);
            double ys = (which_pix1[i].y - which_pix2[j].y) * (which_pix1[i].y - which_pix2[j].y);
            double zs = (which_pix1[i].z - which_pix2[j].z) * (which_pix1[i].z - which_pix2[j].z);
            if (sqrt(xs + ys + zs) < min_dist)
            {
                min_dist = sqrt(xs + ys + zs);
                tmp_min=j;      //calculate the index which is closest
            }
        }

        first.push_back(tmp_min); //this vectors have correct order of second vector based on first vector
    }
//    for (int m=0;m<5;m++){ //for testing order of sorted
//        cout<<"first "<<first[m]<<endl;}

    for (int i = 0; i < which_pix1.size(); i++) {
        _new_pix2.push_back(which_pix2[first[i]]);  //making new ordered vector
        }
    return(_new_pix2);

}


vector<double> calculate_scores() {
    //this function calculates cumulative euclidean distance scores
    vector<Point3D> pix, pixA, pixB, pixC, new_pixA, new_pixB, new_pixC, new_pix;
    pix = Data_Parsed(0);
    pixA = Data_Parsed(1);
    pixB = Data_Parsed(2);
    pixC = Data_Parsed(3);
    vector<double> scorer;
    scorer.clear();
    new_pixA = sorted(pix, pixA);
    new_pixB = sorted(pix, pixB);
    new_pixC = sorted(pix, pixC);
    double sum_score[3]={0,0,0};
    for (int k = 0; k < 3; k++) {

        if (k == 0) {
            new_pix = new_pixA;
        }

        if (k == 1) {
            new_pix = new_pixB;
        }
        if (k == 2) {
            new_pix = new_pixC;
        }
        for (int j = 0; j < pix.size(); j++) {

            double xs = (pix[j].x - new_pix[j].x) * (pix[j].x - new_pix[j].x);
            double ys = (pix[j].y - new_pix[j].y) * (pix[j].y - new_pix[j].y);
            double zs = (pix[j].z - new_pix[j].z) * (pix[j].z - new_pix[j].z);
            sum_score[k]+=sqrt(xs + ys + zs); //cumulative

        }
        scorer.push_back(sum_score[k]); //pushes vector of 3 scores
    }
    return (scorer);
}
int main()

{

 cout<<"lower the score the better the match for A B C"<<endl;
 cout<<"SCORE for A: "<<calculate_scores()[0]<<",  SCORE for B:  "<<calculate_scores()[1]<<",  SCORE for C:  "<<calculate_scores()[2]<<endl;
   //lower the score the better the match

    ofstream myfile ("/Users/mayank/Code/Repos/Teraki_Test/output/result.txt");

    if (myfile.is_open())
    {

        myfile<<"lower the score the better the match for A B C"<<endl;
        myfile << "SCORE for A: "<<calculate_scores()[0]<<",  SCORE for B:  "<<calculate_scores()[1]<<",  SCORE for C:  "<<calculate_scores()[2]<<endl;
        myfile<<"Regards Mayank "<<endl;
        myfile.close();
    }

    return 0;



return(0);
}

