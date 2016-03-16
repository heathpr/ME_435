function varargout = plateLoaderGUI(varargin)
% PLATELOADERGUI MATLAB code for plateLoaderGUI.fig
%      PLATELOADERGUI, by itself, creates a new PLATELOADERGUI or raises the existing
%      singleton*.
%
%      H = PLATELOADERGUI returns the handle to a new PLATELOADERGUI or the handle to
%      the existing singleton*.
%
%      PLATELOADERGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PLATELOADERGUI.M with the given input arguments.
%
%      PLATELOADERGUI('Property','Value',...) creates a new PLATELOADERGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before plateLoaderGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to plateLoaderGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help plateLoaderGUI

% Last Modified by GUIDE v2.5 16-Mar-2016 12:44:24

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @plateLoaderGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @plateLoaderGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
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


% --- Executes just before plateLoaderGUI is made visible.
function plateLoaderGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to plateLoaderGUI (see VARARGIN)

% Choose default command line output for plateLoaderGUI
clc
handles.timeDelays = [0 60 20 30 0;
                      0 0 30 30 0;
                      0 30 0 30 0;
                      0 30 30 0 0;
                      0 30 20 60 0];
handles.output = hObject;
handles.robot=PlateLoaderSim(1);
addImageToAxis('robot_background.jpg',handles.axes_background,700);
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes plateLoaderGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = plateLoaderGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton_reset.
function pushbutton_reset_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_reset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.reset;
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_resetDelays.
function pushbutton_resetDelays_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_resetDelays (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.resetDefaultTimes;
set(handles.text_response,'String',status);
handles.timeDelays = [0 60 20 30 0;
                      0 0 30 30 0;
                      0 30 0 30 0;
                      0 30 30 0 0;
                      0 30 20 60 0];
set(handles.uitable1,'Data',handles.timeDelays(:,2:4));
guidata(hObject, handles);

% --- Executes on button press in pushbutton_setDelay.
function pushbutton_setDelay_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_setDelay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status = handles.robot.setTimeValues(handles.timeDelays);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on selection change in popupmenu_from.
function popupmenu_from_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_from (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_from contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_from
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu_from_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_from (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
guidata(hObject, handles);

% --- Executes on selection change in popupmenu_to.
function popupmenu_to_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_to (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_to contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_to
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenu_to_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_to (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

guidata(hObject, handles);
% --- Executes on button press in pushbutton_movePlate.
function pushbutton_movePlate_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_movePlate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
from=(get(handles.popupmenu_from,'Value'));
to=(get(handles.popupmenu_to,'Value'));
status=handles.robot.movePlate(from,to);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_x1.
function pushbutton_x1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_x1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.x(1);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_x2.
function pushbutton_x2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_x2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.x(2);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton10_x5.
function pushbutton10_x5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton10_x5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.x(5);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_x4.
function pushbutton_x4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_x4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.x(4);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton12_x3.
function pushbutton12_x3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12_x3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.x(3);
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_getStatus.
function pushbutton_getStatus_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_getStatus (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.getStatus;
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_disconnect.
function pushbutton_disconnect_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_disconnect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(handles.checkbox_simulator,'Value')==0
    status=handles.robot.shutdown;
    set(handles.text_response,'String',status);
end
guidata(hObject, handles);

% --- Executes on button press in pushbutton_connect.
function pushbutton_connect_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_connect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get(handles.checkbox_simulator,'Value')==0
    handles.robot=PlateLoader(str2double(get(handles.edit_comPort,'String')));
    status=handles.robot.getStatus;
    set(handles.text_response,'String',status);
end

guidata(hObject, handles);


function edit_comPort_Callback(hObject, eventdata, handles)
% hObject    handle to edit_comPort (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_comPort as text
%        str2double(get(hObject,'String')) returns contents of edit_comPort as a double
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function edit_comPort_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_comPort (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

guidata(hObject, handles);

% --- Executes on button press in checkbox_simulator.
function checkbox_simulator_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_simulator (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_simulator
if get(hObject,'Value')==1
    handles.robot.shutdown;
    handles.robot=PlateLoaderSim(1);
    status=handles.robot.getStatus;
    set(handles.text_response,'String',status);
else
    status=handles.robot.shutdown;
    set(handles.text_response,'String',status);
end
guidata(hObject, handles);

% --- Executes on button press in pushbutton_retract.
function pushbutton_retract_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_retract (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.retract;
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_extend.
function pushbutton_extend_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_extend (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.extend;
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_open.
function pushbutton_open_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_open (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.open;
set(handles.text_response,'String',status);
guidata(hObject, handles);

% --- Executes on button press in pushbutton_close.
function pushbutton_close_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_close (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
status=handles.robot.close;
set(handles.text_response,'String',status);
guidata(hObject, handles);


% --- Executes when entered data in editable cell(s) in uitable1.
function uitable1_CellEditCallback(hObject, eventdata, handles)
% hObject    handle to uitable1 (see GCBO)
% eventdata  structure with the following fields (see UITABLE)
%	Indices: row and column indices of the cell(s) edited
%	PreviousData: previous data for the cell(s) edited
%	EditData: string(s) entered by the user
%	NewData: EditData or its converted form set on the Data property. Empty if Data was not changed
%	Error: error string when failed to convert EditData to appropriate value for Data
% handles    structure with handles and user data (see GUIDATA)
timeDelayChanges = get(hObject, 'Data')
for i= 1:5
    handles.timeDelays(i,2:4) = timeDelayChanges(i,:);
end
handles.timeDelays
guidata(hObject, handles);


