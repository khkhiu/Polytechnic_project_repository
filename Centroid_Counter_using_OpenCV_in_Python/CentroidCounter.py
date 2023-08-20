
##People counter
#numpy is needed for specifying location fo lines as matrix value is needed, and Python alone cannot accomplish the task
import numpy as np
#import CV2 for openCV
import cv2
#import 'Person.py' as it contains all the FX call and classes needed
import Person
#To track time for analytics purposes(to be implemented later, see 'under improvement' section)
import time

#Taking the video input
cap = cv2.VideoCapture(0)
#activate camera.
cap.grab()
cap.read()

#Setting initial values for vars
#cnt_x to count how many people enterred and exited the room
cnt_left  = 0
cnt_right = 0
    

#setting frame height and width of recorded video Using API for video I/O
#.CAP_PROP_FRAME_WIDTH=3
#.CAP_PROP_FRAME_HEIGHT=4
#Also calculating frame threshold for movement detection
FrameWidth = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
FrameHeight = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
FrameArea = FrameHeight*FrameWidth
FrameAreaThreshold = FrameArea/300

#Lines coordinate for counting
line_left = int(1*(FrameHeight/5))
line_right = int(4*(FrameHeight/5))
left_limit = int(.5*(FrameHeight/5))
right_limit = int(4.5*(FrameHeight/5))

#specifying line colours
line_right_color = (255,0,0)#blue
line_left_color = (255,0,255)#purple

#specifying location of entry line(blue)
pt1 =  [300, 0]
pt2 =  [300, 640]
pts_L1 = np.array([pt1,pt2], np.int32)
pts_L1 = pts_L1.reshape((-1,1,2))

#specifying location of exit line(red)
pt3 =  [299, 0]
pt4 =  [299, 640]
#pt3 =  [250, 0]
#pt4 =  [250, 640]
pts_L2 = np.array([pt3,pt4], np.int32)
pts_L2 = pts_L2.reshape((-1,1,2))

#Setting font size
font = cv2.FONT_HERSHEY_SIMPLEX
#Empty list to store people for counting
persons = []
#Set starting number for centroid number
max_p_CentCount = 1
#Set starting ID for centroid number
C_id = 1

#allow camera to stablize
for x in range(20): cap.read()

def preprocess_frame(frame):
    #Convert difference into grayscale, 
    #easier to find contours in grayscale
    #.threshold requires greyscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #.GaussianBlur to smooth colors in  grayscale frames, 
    #'gray' is ths src. Gaussian Kernel Size of 5,5. sigmaX=0, hence sigmaY=0
    #Format->[.GaussianBlur(src, dst, ksize, sigmaX)] 
    #blur = cv2.GaussianBlur(frame, (71,71), 0)
    blur = cv2.GaussianBlur(gray, (61,61), 0)
    return blur

#read the first frame for comparison
ret, frame = cap.read()
frame2 = preprocess_frame(frame)
#while capturing footage
while(cap.isOpened()):
    frame1 = frame2
    frameStartTicks = cv2.getTickCount()
    ret, frame = cap.read()
    frame2 = preprocess_frame(frame)
    
    #absdiff to find absolute difference between 2 frames
    diff = cv2.absdiff(frame1, frame2)

    #.threshold to seperate background from background
    #'ret' not needed as frame always available, hence '_'
    #'blur' is the src, if pixel intensity >20, set threshold to 255
    #Format->[.threshold(src, dst, thresh, maxval, type)]
    _, thresh = cv2.threshold(diff, 10, 255, cv2.THRESH_BINARY)
    
    #cv2.imshow('thresh',thresh)
    
    #improve centroid accuracy by reducing sharp corners introduced by thresh
    blurdiff = cv2.GaussianBlur(thresh, (21,21), 0)
    #cv2.imshow('blurdiff',blurdiff)
    

    #.dilate to increase areas of birght areas, merge close separate spots together
    #Dilate 3 times using 'thresh' as src, kernel size = none
    #Format->[.dilate(src, dst, kernel)]
    dilated = cv2.dilate(blurdiff, None, iterations=40)
    #cv2.imshow('dilated',dilated)
    
    display = frame

    #Drawing contours for movement tracking
    #.findContours to find all boundry points of an image
    #Hierarchy not in use, hence '_'
    #Using 'dilated' as src,'RETR_TREE'retrieves all contours ,
    #'CHAIN_APPROX_SIMPLE' excludes all excessive points and compresses the contour, thereby saving memory
    #Format->[.findContours(src, contour_retrieval, contours_approximation)] 
    contours0, hierarchy = cv2.findContours(dilated,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours0:
        #saving coordinate of discoverred contours
        #.boudingRect to draw rough rectangle around binary img
        rect = cv2.boundingRect(cnt)
        #.contourArea to find area of contour,
        area = cv2.contourArea(cnt)

        #area of contour is in frame threshold
        if area > FrameAreaThreshold:
            #Tracking of movement
            #cv2.moments to make a centroid.
            #M = Moment.
            M = cv2.moments(cnt)
            #cx = x coordinate of the centroid
            cx = int(M['m10']/M['m00'])
            #cy = y coordinate of the centroid
            cy = int(M['m01']/M['m00'])
            # (x,y)->top left coordinate of rectangle
            # (w,h)-> width and height of rectangle
            x,y,w,h = cv2.boundingRect(cnt)

            #New centroid assigned
            new = True
            #if y coordinate of the centroid is within: 48 to 432
            if cy in range(left_limit,right_limit):
                for i in persons:
                    #abs() to return absolute value of number
                    if abs(cx-i.getX()) <= w and abs(cy-i.getY()) <= h:
                        # If object is close to a centroid that has already been detected before, reuse centroid
                        new = False
                        #update coordinates in the object and resets CentCount
                        i.updateCoords(cx,cy)
                        #if centroid going left between frame width 100 and 200
                        if i.going_left(pt3[0],300) == True:  
                            cnt_left += 1
                            print ("Centroid:",i.getId(),'exiting at',time.strftime("%c"))
                        #else if centroid going right between frame width 100 and 200 
                        elif i.going_right(pt3[0],300) == True: 
                            cnt_right += 1
                            print ("Centroid:",i.getId(),'entering at',time.strftime("%c"))
                        break
                    #If centroid exist
                    if i.getState() == '1':
                        if i.getDirect() == 'right' and i.getY() > right_limit:
                            i.setCentOccur()
                        elif i.getDirect() == 'left' and i.getY() < left_limit:
                            i.setCentOccur()
                    #If person moves out of frame
                    if i.MovedOut():
                        #Removed person from list
                        index = persons.index(i)
                        persons.pop(index)
                        #free the memory of i
                        del i     
                #Adds new centroid and increments centroid ID number
                if new == True:
                    p = Person.PersonTracking(C_id,cx,cy, max_p_CentCount)
                    persons.append(p)
                    C_id += 1    

            #Drawing centroid and rectangle
            display = cv2.circle(display,(cx,cy), 5, (0,0,255), -1)
            display = cv2.rectangle(display,(x,y),(x+w,y+h),(0,255,0),2)            
              
    #Numbers the centroid 
    for i in persons:
        if (i.state == '0'): i.stationaryFrames = i.stationaryFrames + 1
        if (i.stationaryFrames > 40): i.setCentOccur()
        cv2.putText(display, str(i.getId()),(i.getX(),i.getY()),font,1,(0, 255, 255),1,cv2.LINE_AA)
        
    #Displaying Information on frame
    str_left = 'Exit: '+ str(cnt_left)
    str_right = 'Enter: '+ str(cnt_right)
    str_people = "PEOPLE: " + str(cnt_right - cnt_left)
    
    #Setting lines to determine entry and exit points
    display = cv2.polylines(display,[pts_L1],False,line_right_color,thickness=2)
    display = cv2.polylines(display,[pts_L2],False,line_left_color,thickness=2)
    #Specifying text placement for counter
    cv2.putText(display, str_left ,(10,40),font,0.5,(255,255,255),2,cv2.LINE_AA)
    cv2.putText(display, str_left ,(10,40),font,0.5,(0,0,255),1,cv2.LINE_AA)
    cv2.putText(display, str_right ,(10,90),font,0.5,(255,255,255),2,cv2.LINE_AA)
    cv2.putText(display, str_right ,(10,90),font,0.5,(255,0,0),1,cv2.LINE_AA)
    cv2.putText(display, str_people ,(10,65),font,0.5,(255,255,255),2,cv2.LINE_AA)
    cv2.putText(display, str_people ,(10,65),font,0.5,(0,255,0),1,cv2.LINE_AA)
    
    #set label at top of video
    cv2.imshow('Feed',display)

    peopleEntered = max(cnt_right-cnt_left, 0) #not supposed to be smaller than zero.
  
    #press 'q' to quit
    if cv2.waitKey(1) == ord('q'):
        break
    
    frameEndTicks = cv2.getTickCount()
    #print((frameEndTicks - frameStartTicks)/ cv2.getTickFrequency())


#close window
cv2.destroyAllWindows()
#release resources use by 'cap'
cap.release()
