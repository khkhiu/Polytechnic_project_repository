***

<strong>Introduction</strong>

***
The aim of the project is to develop a simple algorithm to count the number of people in the room. This algorithm was part of a bigger project, for <cite><a href="https://www.sp.edu.sg/engineering-cluster/eee/engineering-academy/the-programme">the Engineering Academy Programme</a></cite> but his repository will only focus on the algorithm.

***

<strong>The team</strong>

***
The following are members of the team(As of 7 Sep 2021)

1. Khiu Kim Hong, Diploma in Electrical and Electronic Engineering
2. Cheam Zhi Kai, Diploma in Engineering with Business
3. Ang Yong En, Diploma in Computer Engineering
4. Chan Qing Yi, Diploma in Mechanical Engineering
5. Ngo Bing Han, Diploma in Electrical and Electronic Engineering

***

<strong>Solution</strong>

***

Using OpenCV and python, the team achieved the aim using centroids. The way we ‘count’ the number of people in the room is by detecting centroids moving pass a given threshold. A centroid is created and given an ID number when movement is detected. If the centroid moves past the ‘entry’ threshold, the program counts it as a person entering the room. Similarly, if a centroid moves past the ‘exit’ threshold, the program counts it as a person leaving the room.

If movement is detected near an existing centroid, that centroid is reused instead of making a new one. 


***

<strong>Video demonstration</strong>

***

[![Singapore Polytechnic - Centroid Counter](http://img.youtube.com/vi/nILaMWWoH28/0.jpg)](http://www.youtube.com/watch?v=nILaMWWoH28)
