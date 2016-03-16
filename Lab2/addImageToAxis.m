function [ imageObject ] = addImageToAxis( imageFileName, axesHandle,axesWidth )
%ADDIMAGETOAXIS adds an image to an axes
%   opens the image file name and adds it to the axis
%   return the image object
%   if axesWidth = 0 then use images default pixel size


% Open the file to get the image data
imageData=imread(imageFileName);

% create image object and make the parent the axes
imageObject=image(imageData, 'Parent',axesHandle);

% Make the units of the axes 'pixels'
% Visible off
set(axesHandle,'Units','Pixels','Visible','Off')

% Get the current 'Position' of the Axes so that we can use the x and y
currentPosition=get(axesHandle,'Position');


[rowsHeight,colsWidth,depth] = size(imageData);
if axesWidth == 0
    axesWidth = colsWidth;
    axesHeight = rowsHeight;
else 
%     use the axesWidth and aspect ratio to calculate the height
    axesHeight = axesWidth * rowsHeight / colsWidth;

end

% set the new 'Posiition' on the axes
set(axesHandle,'Position',[currentPosition(1) currentPosition(2) axesWidth axesHeight]);

end

