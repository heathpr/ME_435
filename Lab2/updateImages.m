function   updateImages( handles )
% updateImages function to update the display of the GUI
%   uses the properties of the GUI to set the proper images and loactions
%   for the images of the robot.

%% gets current state of the robot
[x, z, gripper, plate]=handles.robot.getProperties;

%% coordinates the image moves to 
x1=[1,1];
x2=[1,1];
x3=[1,1];
x4=[1,1];
x5=[1,1];

z1=[1,1];
z2=[1,1];
z3=[1,1];
z4=[1,1];
z5=[1,1];

%% move Z-axis
if z==1 % gripper extended
   addImageToAxis('extended_bars.jpg',handles.axes_zAxis,0)
   set(handles.axes_zAxis,'Visible',1);
else % gripper retracted
    set(handles.axes_zAxis,'Visible',0);
end


%% 
end

