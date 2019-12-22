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
{   
    

    vector<long double> input;
    string word = ""; 
    for (auto x : _str) 
    {  
       if (x == ' ') 
       {   
        //    cout << word << endl; 
           input.push_back(stold (word));
           
           word = ""; 
       } 
       else
       { 
           word = word + x; 
       } 
   } 

    long double arr[input.size()];
    copy(input.begin(), input.end(), arr);
    if (_fileNo==0)
    {
     pixels.push_back({arr[0],arr[1],arr[2]});
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
    string input_file_dir="/Users/mayank/Code/Repos/Teraki_Test/input/" ;
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
        if (31< i && i< 2141)
        {
            // cout << i<<"||"<<line << endl;
            removeDupWord(line,fileNo);
        }
    }
    // close the file stream
    // cout<<pixels.size()<<pixels[0].x<<" "<<pixels[pixels.size()-1].z<<endl;
    inFile.close();

//    vector<Point3D> A;
    if (fileNo==0)
    {return(pixels);
    }
    if (fileNo==1)
    {return(pixelsA);
    }
    if (fileNo==2)
    {return(pixelsB);
    }
    if (fileNo==3)
    {return(pixelsC);
    }
}

//double score_calculator(vector<Point3D> which_pix1, vector<Point3D> which_pix2) {
vector<Point3D>  sorted(vector<Point3D> which_pix1, vector<Point3D> which_pix2) {
    vector<Point3D> _new_pix2;
    _new_pix2.clear();
    int tmp_min;
    vector<int> first;
    for (int i = 0; i < which_pix1.size(); i++) {
        long double min_dist = 10;                //arbitary to calculate minimum
        for (int j = 0; j < which_pix2.size(); j++) {

            double xs = (which_pix1[i].x - which_pix2[j].x) * (which_pix1[i].x - which_pix2[j].x);
            double ys = (which_pix1[i].y - which_pix2[j].y) * (which_pix1[i].y - which_pix2[j].y);
            double zs = (which_pix1[i].z - which_pix2[j].z) * (which_pix1[i].z - which_pix2[j].z);
            if (sqrt(xs + ys + zs) < min_dist)
            {
                min_dist = sqrt(xs + ys + zs);
                tmp_min=j;
            }
        }

        first.push_back(tmp_min);
    }

    for (int i = 0; i < which_pix1.size(); i++) {
        _new_pix2.push_back(which_pix2[first[i]]);

        }
    return(_new_pix2);

}


vector<double> calculate_scores() {
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
            sum_score[k]+=sqrt(xs + ys + zs);

        }
        scorer.push_back(sum_score[k]);
    }
    return (scorer);
}
int main()

{
    for (int i=0;i<3;i++)
{    cout<<calculate_scores()[i]<<endl;}      //lower the score the better the match



return(0);
}

