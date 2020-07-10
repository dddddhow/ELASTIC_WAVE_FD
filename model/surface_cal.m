clc,clear;

%% Model load
nz = 600;
nx = 400;
dz = 5;
dx = 5;
sx = 200;
offset = 100;


model    = zeros(nz,nx);
fp_model = fopen('model_nz600_nx400.dat','rb');
model    = fread(fp_model,[nz nx],'float32');
fclose(fp_model);

% imagesc(model);

%% Calculate the location of the surface
surface = zeros(nx);

for ix = 1 : nx
    flag_surface = 0;
    for iz = 1 : nz-1
        if(model(iz+1,ix) >= 2*model(iz,ix) && flag_surface == 0)
            surface(ix) = iz;
            flag_surface = 1 ;
        end       
    end
end

fp_surface = fopen('surface_all.dat','w');
fwrite(fp_surface,surface(1:nx),'float32');
fclose(fp_surface);


%% Find out the Geo_line of a certain shot lacation
geo_line = zeros(offset);
side=offset/2;
geo_line = surface(sx-side:sx+side);


%change geo_line to the file_format that the SU ask
geo_line_save=zeros(200);
for i=1:1:offset
    geo_line_save(i*2) = i;
    geo_line_save(i*2-1) = geo_line(i);
end

save('pqfile.txt','geo_line_save','-ascii')



fp_surface_signal = fopen('surface_singal.dat','w');
fwrite(fp_surface_signal,geo_line_save(1:2*offset),'float32');
fclose(fp_surface_signal);


imagesc(model),hold on;
plot(sx-side:sx+side,geo_line,'r'),hold on;
plot(sx:sx+1,geo_line(1504:1505),'-o');





