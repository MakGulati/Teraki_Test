#include <iostream>
#include <fstream>
#include <vector> 

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
           input.push_back(stod (word));
           
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
vector<Point3D> Data_Parsed(int fileNo=0)
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
    
    // open the file stream
    string input_file_dir="/Users/mayank/Code/Repos/Teraki3DRecruitmentTestApr19/input/";
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
        if (31< i && i< 2141 )
        {
            // cout << i<<"||"<<line << endl;
            removeDupWord(line,fileNo);
        }
    }
    // close the file stream
    // cout<<pixels.size()<<pixels[0].x<<" "<<pixels[pixels.size()-1].z<<endl;
    inFile.close();


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



int main()

{
    // cout<<Data_Parsed(2).size()<<"  "<<Data_Parsed(2)[0].x<<"    "<<Data_Parsed(2)[Data_Parsed(2).size()-1].z<<endl;
    cout<<Data_Parsed(1)[Data_Parsed(1).size()-1].x<<"  "<<Data_Parsed(1)[Data_Parsed(1).size()-1].y<<"    "<<Data_Parsed(1)[Data_Parsed(1).size()-1].z<<endl;
    
}

