import numpy as np
from numpy import cos,sin,pi
import matplotlib.pyplot as plt

from firebase import firebase
firebase = firebase.FirebaseApplication('FIREBASE LINK',None)
directory="/ultrasonic_value"
datas=[]
num = firebase.get(directory+"/NumberOfValues",None)
for i in range(num):
    incoming=firebase.get(directory+"/Number"+str(i),None)
    datas.append(incoming)
  
#datas=[10.5,1,10.9,0,15.1,0,40.8,0,25.1,0,10.4,0,10.5,1,10.6,1,10.9,0,10.7]
#datas=[132,1,27,1,128,1,28]
# Convert data into floats, for 
sensor_data = tuple(map(lambda x: float(x),datas))

# Start at 0,0 in a 2D plane and start out in x-Direction
Starting_Position = np.array((0.,0.))
#print("Start pos initialisation")
#print(Starting_Position)
Starting_Direction = np.array((1.,0.))
#print("Start dir initialisation")
#print(Starting_Direction)

def Rotation_Matrix(direction):

    '''Can be expanded for any angle of rotation in a 2D plane. Google rotation matrix in 2D space.'''

    a = {'left':pi/2,'right':-pi/2}[direction]

    matrix = np.array(((round(cos(a),7),round(-sin(a),7)),
                       (round(sin(a),7),round(cos(a),7))))
    print(matrix)
    return matrix



def DronePosition(Number_input,Current_Position,Current_Direction):

    if Number_input == 1.:
        New_Direction = Current_Direction.dot(Rotation_Matrix('left'))
        New_Position = Current_Position
    elif Number_input == 0.:
        New_Direction = Current_Direction.dot(Rotation_Matrix('right'))
        New_Position = Current_Position
    else:
        New_Position = Current_Position + Current_Direction*Number_input
        New_Direction = Current_Direction


    return New_Position,New_Direction

Drone_Path = np.zeros(shape=(len(sensor_data),2))
#print("Drone path array")
#print(Drone_Path)
for step in range(len(sensor_data)):
    Drone_Path[step,0] = Starting_Position[0]
    print("hi")
    print(Drone_Path[step,0])
    Drone_Path[step,1] = Starting_Position[1]
    print("Final",Drone_Path)
    Starting_Position, Starting_Direction = DronePosition(sensor_data[step],Starting_Position,Starting_Direction)
    print("After update",Starting_Position,"\n",Starting_Direction)

fig, ax = plt.subplots(figsize=(6,6))
#print(Drone_Path)
ax.plot(Drone_Path[:,0],Drone_Path[:,1])
plt.show()
