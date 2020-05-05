## profile develop environment build

sudo yum localinstall google-chrome-stable_current_x86_64.rpm
sudo yum localinstall wps-office-11.1.0.9505-1.x86_64.rpm
yum list installed | grep yum-utils 
sudo vim /etc/yum.repos.d/CentOS-Debuginfo.repo 
sudo yum install ibus-libpinyin.x86_64 
sudo yum -y install libxml2 libxml2-devel
sudo yum install openssl openssl-devel
sudo yum install bzip2 bzip2-devel -y
sudo yum install curl curl-devel
sudo yum install libjpeglibjpeg -devel
sudo yum install libjpeg-devel
sudo yum install libpng libpng-devel
sudo yum install freetype-devel
sudo yum -y install libxslt libxslt-devel
yum info docker
sudo yum install -y yum-utils device-mapper-persistent-data lvm2

