#Class for tracking a person
class PersonTracking:
    #initializing the attributes: (self, i, xi, yi, max_CentCount)
    def __init__(self, i, xi, yi, max_CentCount):
        #Using 'self.' to make every variable available to every method in PersonTracking
        #'i' to store centroid ID number
        #'xi' to store x-axis coordinate of centroid
        #'yi' to store y-axis coordinate of centroid 
        self.i = i
        self.x = xi
        self.y = yi
        #Creating empty list called: tracks 
        #'Tracks' direction of centroid
        self.CentTrackDirect = []

        #Vars for making centroid appear
        #Default = no centroid appearing
        self.CentOccur = False
        self.state = '0'
        #Centroid number counting starting from zero
        self.CentCount = 0
        self.max_CentCount = max_CentCount
        #Var for Direction
        #Default = no direction
        self.direct = None
        self.stationaryFrames = 0

    def getCentTrackDirect(self):
        return self.CentTrackDirect
    #FX call to retrieve centroid ID number
    def getId(self):
        return self.i
    #FX call to retrive x and y axis coordinate values
    def getX(self):
        return self.x
    def getY(self):
        return self.y    
    #FX call to make centroid appear
    def getState(self):
        return self.state
    #FX call to track direction
    def getDirect(self):
        return self.direct
    #FX call to retrive x and y axis coordinate values
    def updateCoords(self, xn, yn):
        self.CentCount = 0
        #Adds x and y axis coordinates to CentTrackDirect list
        #Y coordinate first to to track with frame width instead of frame height
        self.CentTrackDirect.append([self.y,self.x])
        self.x = xn
        self.y = yn

    #Make Centroid appear when movement is detected
    def setCentOccur(self):
        self.CentOccur = True

    #Defining FX for when people move out of frame
    #Remove centroid, this self.CentOccur = False
    def MovedOut(self):
        return self.CentOccur

    #Defining FX for centroid moving left
    def going_left(self,start_right,end_left):
        if len(self.CentTrackDirect) >= 2:
            #if centroid not moving
            if self.state == '0':
                # if width x height < 96 AND width x height >=96
                if self.CentTrackDirect[-1][1] < end_left and self.CentTrackDirect[-2][1] >= end_left:
                    #Make centroid appear and set direction to left
                    state = '1'
                    self.direct = 'left'
                    return True
            else:
                return False
        else:
            return False

    #Defining FX for centroid moving right
    def going_right(self,start_right,end_left):
        if len(self.CentTrackDirect) >= 2:
            #if centroid not moving
            if self.state == '0':
                # if width x height < 96 AND width x height >=96
                if self.CentTrackDirect[-1][1] > start_right and self.CentTrackDirect[-2][1] <= start_right:     
                    #make centroid appear if right movement detected and set direction as right
                    state = '1'
                    #mid_start=384
                    self.direct = 'right'
                    return True
            else:
                return False
        else:
            return False

    #FX for increasing the number of centroid
    def CentCount_one(self):
        self.CentCount += 1
        if self.CentCount > self.max_CentCount:
            self.CentOccur = True
        return True


  

