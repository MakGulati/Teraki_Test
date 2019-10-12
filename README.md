# Background

Welcome to the C++ coding test for the position advertised in April 2019 (https://teraki.bamboohr.com/jobs/view.php?id=36).

At Teraki, the focus of research in the point cloud team are compression, object detection, segmentation and SLAM (Simultaneous Localization and Mapping). We work mainly with LiDAR or Time-of-Flight data.

Most of the in-house development of algorithms are in C++. Sometimes, Python comes in handy when we want to do data analysis and plotting.

To help us know you better, we would like to see how you:

* code in C++
* handle a CMake project
* version your code with Git

In addition, we would like to see how you choose your algorithm (in terms of efficiency, CPU and memory used). It will be great if you explain briefly why you made this choice. 

We will also take into consideration if the code respects general good practice, such as being well documented and easily extensible to adding new features.

# How to format and send us your code and results

We already provide a structure of a `Git` repository. Please develop in this structure, and then post it a private version of GitHub (we understand a private account is free in GitHub starting from recently). Make it it available to read to `abuzatu`, `mholzel`, `paulsabyasachi`. Please reply to our email by giving us the name of your repository.  We want to do simply clone your repository, cd into into and run `./run.sh` from the root directory of the repository. For example.

```
git clone https://github.com/abuzatu/Teraki3DRecruitmentTestApr19.git
cd Teraki3DRecruitmentTestApr19
./run.sh
```

Then explore the results printed in the terminal, or presented in files in the `output` folder.

Note that `run.sh` needs to be run from the root directory of the repository and you will have to update it with your own executables.

We provide a skeleton of `run.sh` and of the folder `code`, that contains `build` and `source`. Please put your .h and .cxx or .cpp in `source`, along with the `CMakeLists.txt`. Compilation is done in the build folder. The script `run.sh` gives already a skeleton of how to launch the compilation (either both cmake and make - to do when you add new files), or only make (to do when current files are being modified), then run the executables that you decide. 

So simply add the code in `code/source` and update `run.sh` with the executables you want to be run. There can be several, if you prefer to. Note that `run.sh` should be run from the root folder of the repository. 

The output of your code would go to `output` (text files, plots, etc). Just in case your code would not compile directly for us (some of us use `MacOS`, some `Linux`, some `Windows`), store these file in `output` also in `Git`.

# The C++ and data analysis task

We provide you with a 3D point cloud representation of a car. This is a subset of an actual recording taken with a `Velodyne` `LiDAR` from the public dataset Kitti. Each point has the following characteristics: the coordinates `x`, `y`, `z` and the reflectivity `r`. Such a point cloud can be visualised in 3D for example with the free software [CloudCompare](http://www.danielgm.net/cc/release/). 

The original (uncompressed) point cloud is found at `input/Car_XYZI_uncompressed_ASCII.ply`. A screenshot from CloudCompare for this point cloud is found at `input/Car_uncompressed.png`. Each points are colored differently as they have different reflectivity values.

Three decompressed files are available in `input/Car_XYZI_decompressed_ASCII_A.ply`, `input/Car_XYZI_decompressed_ASCII_B.ply`, `input/Car_XYZI_decompressed_ASCII_C.ply`, each produced with a different compression parameter.

Your data analysis task is to rank the compressions methods `A`, `B` and `C` from best to worse accuracy. To make it simple, you can ignore the reflectivity numbers, and focus on the geometry (`x`,`y`,`z`). First obtain a qualitative answer quickly by eye by using `CloudCompare`. Load the four `.ply` files, and look at them one at a time, then also overlaying the uncompressed with one decompressed file, and do it for the three options.

But to compare rigourously the three compression optons, an answer has to be quantitative. To achieve this, you need to solve the `C++` task. 

Although the uncompressed and compressed point clouds in the two `.ply` files contain the same number of points (one point being one line in the file), the points do not appear in the same order. First you need to re-arrange the points in the decompressed point cloud to be in the same order as those in the compressed point clouds. The choice is made by having the smallest cartesian distance. That is, for each point in the uncompressed point cloud, study the points in the decompressed point cloud and find the one that is closest to it. 

Add your code in `code/source`, update `run.sh` so that when running this script, a text file is created in the  `output` folder. The file is to contain the list of points with the values: `x_uncompressed`, `y_uncompressed`, `z_uncompressed`, `z_decompressed`, `y_decompressed`, `z_decompressed`, `distance`.

Study these values of distance and introduce one or several figures of merit that characterize the geometry accuracy of the compression (Hint: Geometry accuracy can be maximum/average distance between the point sets of uncompressed and ordered decompressed point cloud). 

Do you obtain the same order as you obtained qualitatively by eye with `CloudCompare`?

For this part, you can use Python, if you prefer, for example to parse the previous output file for distances, manipulate them, create some plots. 

Note that while there are open source libraries that achieve this task, and which we may use in a real day to day job, the task is for your to code this yourself, to test your coding and problem solving skills.

Please add a report either in another `README` file, or in a `pdf` file in the output file. Make sure you explain why you designed the code as you did, why did you choose these algorithms, what choices you made to make sure the code runs efficiently, fast, with as few and possible CPU and RAM resources. In addition to the coding test, please also make sure you explain the `data analysis` questions how do the three compressions ranks, of how you chose the figure of merit to do the ranking. And if you had more time or computing resources, how would you improve the results.

Thank you for taking a look at the task of studying compression on a point cloud representing a car. Please add your code in `code/source`, update `run.sh` with the executables you want us to run, which will put your results (text files, plots, etc) into `output`. Copy your `output` to `output_final` or similar, so that we have a list of your own output. And keep `output` folder empty. 

# Conclusion

We expect to test your solution by simply running `./run.sh`. This should compile your code, run it, and put the output in the output folders. For your report we will look in `output_folder`. Then send us via email the Git repository with your solution! Good luck!
