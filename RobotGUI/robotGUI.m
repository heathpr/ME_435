function varargout = robotGUI(varargin)
%ROBOTGUI M-file for robotGUI.fig
%      ROBOTGUI, by itself, creates a new ROBOTGUI or raises the existing
%      singleton*.
%
%      H = ROBOTGUI returns the handle to a new ROBOTGUI or the handle to
%      the existing singleton*.
%
%      ROBOTGUI('Property','Value',...) creates a new ROBOTGUI using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to robotGUI_OpeningFcn.  This calling syntax produces a
%      warning when there is an existing singleton*.
%
%      ROBOTGUI('CALLBACK') and ROBOTGUI('CALLBACK',hObject,...) call the
%      local function named CALLBACK in ROBOTGUI.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help robotGUI

% Last Modified by GUIDE v2.5 05-Apr-2016 20:28:54

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @robotGUI_OpeningFcn, ...
    'gui_OutputFcn',  @robotGUI_OutputFcn, ...
    'gui_LayoutFcn',  [], ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before robotGUI is made visible.
function robotGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)
clc

% Choose default command line output for robotGUI
handles.output = hObject;

% Set Joint angle panel max and mins
set(handles.text_slide1Max,'String',get(handles.slider_1,'Max'))
set(handles.text_slide1Min,'String',get(handles.slider_1,'Min'))
set(handles.text_slide2Max,'String',get(handles.slider_2,'Max'))
set(handles.text_slide2Min,'String',get(handles.slider_2,'Min'))
set(handles.text_slide3Max,'String',get(handles.slider_3,'Max'))
set(handles.text_slide3Min,'String',get(handles.slider_3,'Min'))
set(handles.text_slide4Max,'String',get(handles.slider_4,'Max'))
set(handles.text_slide4Min,'String',get(handles.slider_4,'Min'))
set(handles.text_slide5Max,'String',get(handles.slider_5,'Max'))
set(handles.text_slide5Min,'String',get(handles.slider_5,'Min'))

% Set Gripper max and mins
set(handles.text_gripperMin,'String',get(handles.slider_gripper,'Min'))
set(handles.text_gripperMax,'String',get(handles.slider_gripper,'Max'))

% boolean for connection
handles.user.isConected=0;

% create arm stuff
% Prepare the arm axes
view(handles.axes_arm, [-50 -50 50]);
axis(handles.axes_arm, [-13 10 -8 8 -3 14.5]);
grid on
xlabel('x')
ylabel('y')
zlabel('z')

% Create vertices for all the patches
makeLink0(handles.axes_arm, [.5 .5 .5]);  % Doesn't move. No handles needed.
% Save handles to the patch objects.
% Save references to the vertices of each patch, make points 4x1 not 3x1.
handles.user.link1Patch = makeLink1(handles.axes_arm, [.9 .9 .9]);
handles.user.link1Vertices = get(handles.user.link1Patch, 'Vertices')';
handles.user.link1Vertices(4,:) = ones(1, size(handles.user.link1Vertices,2));
handles.user.link2Patch = makeLink2(handles.axes_arm, [.9 .9 .9]);
handles.user.link2Vertices = get(handles.user.link2Patch, 'Vertices')';
handles.user.link2Vertices(4,:) = ones(1, size(handles.user.link2Vertices,2));
handles.user.link3Patch = makeLink3(handles.axes_arm, [.9 .9 .9]);
handles.user.link3Vertices = get(handles.user.link3Patch, 'Vertices')';
handles.user.link3Vertices(4,:) = ones(1, size(handles.user.link3Vertices,2));
handles.user.link4Patch = makeLink4(handles.axes_arm, [.9 .9 .9]);
handles.user.link4Vertices = get(handles.user.link4Patch, 'Vertices')';
handles.user.link4Vertices(4,:) = ones(1, size(handles.user.link4Vertices,2));
handles.user.link5Patch = makeLink5(handles.axes_arm, [.95 .95 0]);
handles.user.link5Vertices = get(handles.user.link5Patch, 'Vertices')';
handles.user.link5Vertices(4,:) = ones(1, size(handles.user.link5Vertices,2));

% set display
handles.user.jointAngles=[0, 0, 0, 0, 0];
jointSliderChange(handles);
addImageToAxis('wildThumper.png',handles.axes_base,0)




% Update handles structure
guidata(hObject, handles);

% UIWAIT makes robotGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = robotGUI_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit_COMPort_Callback(hObject, eventdata, handles)
% hObject    handle to edit_COMPort (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_COMPort as text
%        str2double(get(hObject,'String')) returns contents of edit_COMPort as a double


% --- Executes during object creation, after setting all properties.
function edit_COMPort_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_COMPort (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_open.
function pushbutton_open_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_open (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%close open ports
open_ports = instrfind('Type','serial','Status','open');
if ~isempty(open_ports)
    fclose(open_ports);
end

comPort=sprintf('COM%c',get(handles.edit_COMPort,'String'));
handles.robot = serial(comPort, 'Baudrate', 9600);
fopen(handles.robot);

handles.user.isConected = 1;

guidata(hObject, handles);




% --- Executes on button press in pushbutton_close.
function pushbutton_close_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_close (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%close open ports
open_ports = instrfind('Type','serial','Status','open');
if ~isempty(open_ports)
    fclose(open_ports);
end
handles.user.isConected=0;

guidata(hObject, handles);


% --- Executes on slider movement.
function slider_gripper_Callback(hObject, eventdata, handles)
% hObject    handle to slider_gripper (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
if(handles.user.isConected==1)
    grip= sprintf('GRIPPER %d', get(handles.slider_gripper,'Value'));
fprintf(handles.robot, grip);
end
guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function slider_gripper_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_gripper (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_1_Callback(hObject, eventdata, handles)
% hObject    handle to slider_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
jointSliderChange(handles);



% --- Executes during object creation, after setting all properties.
function slider_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_2_Callback(hObject, eventdata, handles)
% hObject    handle to slider_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
jointSliderChange(handles);



% --- Executes during object creation, after setting all properties.
function slider_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_3_Callback(hObject, eventdata, handles)
% hObject    handle to slider_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
jointSliderChange(handles);



% --- Executes during object creation, after setting all properties.
function slider_3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_4_Callback(hObject, eventdata, handles)
% hObject    handle to slider_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
jointSliderChange(handles);



% --- Executes during object creation, after setting all properties.
function slider_4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider_5_Callback(hObject, eventdata, handles)
% hObject    handle to slider_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
jointSliderChange(handles);


% --- Executes during object creation, after setting all properties.
function slider_5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% update slider text
function jointSliderChange(handles)

handles.user.jointAngles(1)=round(get(handles.slider_1, 'Value'));
handles.user.jointAngles(2)=round(get(handles.slider_2, 'Value'));
handles.user.jointAngles(3)=round(get(handles.slider_3, 'Value'));
handles.user.jointAngles(4)=round(get(handles.slider_4, 'Value'));
handles.user.jointAngles(5)=round(get(handles.slider_5, 'Value'));

jointAnglesStr=sprintf('%d   %d   %d   %d   %d',handles.user.jointAngles);
set(handles.text_jointAngles,'String',jointAnglesStr);
updateArm('unused', handles);
if(handles.user.isConected==1)
    updateRobotArm('unused',handles);
end





function updateArm(hObject, handles)

% DONE: Make sure the handles.user.jointAngles values are set.

% DONE: Create the five homogeneous transformation matrices.
[A1,A2,A3,A4,A5] = makeHomogeneousTransformations(handles.user.jointAngles(1),...
    handles.user.jointAngles(2),handles.user.jointAngles(3),handles.user.jointAngles(4),...
    handles.user.jointAngles(5));

% DONE: Use the A matricies to form the T0_n matricies.
T0_1 = A1;
T0_2 = A1*A2;
T0_3 = A1*A2*A3;
T0_4 = A1*A2*A3*A4;
T0_5 = A1*A2*A3*A4*A5;

% DONE: Use the T matricies to transform the patch vertices
link1verticesWRTground = T0_1 * handles.user.link1Vertices;
link2verticesWRTground = T0_2 * handles.user.link2Vertices;
link3verticesWRTground = T0_3 * handles.user.link3Vertices;
link4verticesWRTground = T0_4 * handles.user.link4Vertices;
link5verticesWRTground = T0_5 * handles.user.link5Vertices;

% DONE: Update the patches with the new vertices
set(handles.user.link1Patch,'Vertices', link1verticesWRTground(1:3,:)');
set(handles.user.link2Patch,'Vertices', link2verticesWRTground(1:3,:)');
set(handles.user.link3Patch,'Vertices', link3verticesWRTground(1:3,:)');
set(handles.user.link4Patch,'Vertices', link4verticesWRTground(1:3,:)');
set(handles.user.link5Patch,'Vertices', link5verticesWRTground(1:3,:)');


% Optional code (if you want to display the XYZ of the gripper).
% Update x, y, and z using the gripper (end effector) origin.
dhOrigin = [0 0 0 1]';
gripperWRTground = T0_5 * dhOrigin;
position=sprintf('X = %.3f", Y = %.3f", Z = %.3f"\n', gripperWRTground(1), gripperWRTground(2), gripperWRTground(3));
set(handles.text_position,'String',position);



function updateRobotArm(hObject,handles)
% send messages to robot to update all positions of the arm
pos = sprintf('POSITION %d %d %d %d %d',handles.user.jointAngles(1),...
    handles.user.jointAngles(2),handles.user.jointAngles(3),handles.user.jointAngles(4),handles.user.jointAngles(5));
fprintf(handles.robot, pos);
