clc
close all
clear variables


%close any open conections 
open_ports=instrfind('Type','serial','Status','open');
if ~isempty(open_ports)
    fclose(open_ports);
end

fprintf('Connecting to Robot...')
s=serial('COM4','BaudRate',19200,'Terminator',10,'Timeout',5);
fprintf('\nStatus os %s\n',s.Status)
fprintf('Opening...\n')
fopen(s);
fprintf('Status is %s\n',s.Status)
fprintf(s,'INITIALIZE');
fprintf(getResponse(s));
fprintf(s,'Move 5 1');
fprintf(getResponse(s));
fprintf(s,'Move 4 2');
fprintf(getResponse(s));
fprintf(s,'Move 1 4');
fprintf(getResponse(s));
fprintf(s,'Move 2 5');
fprintf(getResponse(s));
