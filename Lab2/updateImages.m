function   updateImages( handles )
% updateImages function to update the display of the GUI
%   uses the properties of the GUI to set the proper images and loactions
%   for the images of the robot.

%% gets current state of the robot
[x, z, gripper, plate]=handles.robot.getProperties;

%% coordinates the image moves to
xu1=[315,476];
xu2=[434,476];
xu3=[547,476];
xu4=[665,476];
xu5=[785,476];

xd1=[315,357];
xd2=[434,357];
xd3=[547,357];
xd4=[665,357];
xd5=[785,357];

z1=[370,439];
z2=[485,439];
z3=[599,439];
z4=[720,439];
z5=[835,439];

%% move Z-axis
if z==1 % gripper extended
    addImageToAxis('extended_bars.jpg',handles.axes_zAxis,0)
    set(get(handles.axes_zAxis,'Children'),'Visible','on');
else % gripper retracted
    addImageToAxis('extended_bars.jpg',handles.axes_zAxis,0)
    set(get(handles.axes_zAxis,'Children'),'Visible','off');
end


%% determine gripper image
if gripper==1 % gripper closed
    if plate==1 % plate present
        addImageToAxis('gripper_with_plate.jpg',handles.axes_gripper,160);
    else % no plate present
        addImageToAxis('gripper_closed_no_plate.jpg',handles.axes_gripper,160);
    end
else % open
    addImageToAxis('gripper_open_no_plate.jpg',handles.axes_gripper,160);
    
end

%% determine locations
zpos=get(handles.axes_zAxis,'Position');
xpos=get(handles.axes_gripper,'Position');
switch x
    case 1
        set(handles.axes_zAxis,'Position',[z1(1) z1(2) zpos(3) zpos(4)]);
        if z==1
            set(handles.axes_gripper,'Position',[xd1(1) xd1(2) xpos(3) xpos(4)]);
        else
            set(handles.axes_gripper,'Position',[xu1(1) xu1(2) xpos(3) xpos(4)]);
        end
    case 2
        set(handles.axes_zAxis,'Position',[z2(1) z2(2) zpos(3) zpos(4)]);
        if z==1
            set(handles.axes_gripper,'Position',[xd2(1) xd2(2) xpos(3) xpos(4)]);
        else
            set(handles.axes_gripper,'Position',[xu2(1) xu2(2) xpos(3) xpos(4)]);
        end
    case 3
        set(handles.axes_zAxis,'Position',[z3(1) z3(2) zpos(3) zpos(4)]);
        if z==1
            set(handles.axes_gripper,'Position',[xd3(1) xd3(2) xpos(3) xpos(4)]);
        else
            set(handles.axes_gripper,'Position',[xu3(1) xu3(2) xpos(3) xpos(4)]);
        end
    case 4
        set(handles.axes_zAxis,'Position',[z4(1) z4(2) zpos(3) zpos(4)]);
        if z==1
            set(handles.axes_gripper,'Position',[xd4(1) xd4(2) xpos(3) xpos(4)]);
        else
            set(handles.axes_gripper,'Position',[xu4(1) xu4(2) xpos(3) xpos(4)]);
        end
    case 5
        set(handles.axes_zAxis,'Position',[z5(1) z5(2) zpos(3) zpos(4)]);
        if z==1
            set(handles.axes_gripper,'Position',[xd5(1) xd5(2) xpos(3) xpos(4)]);
        else
            set(handles.axes_gripper,'Position',[xu5(1) xu5(2) xpos(3) xpos(4)]);
        end
end
end

