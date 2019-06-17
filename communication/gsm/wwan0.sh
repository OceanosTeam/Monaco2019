echo "wwan0 Network Setup Script"

sudo qmicli -d /dev/cdc-wdm0 --dms-set-operating-mode='online'
sudo qmicli -d /dev/cdc-wdm0 --dms-get-operating-mode
sudo qmicli -d /dev/cdc-wdm0 --nas-get-signal-strength
sudo qmicli -d /dev/cdc-wdm0 --nas-get-home-network

sudo qmicli -d /dev/cdc-wdm0 -w		# this confirms the name of the network interface, typically wwan0
sudo ip link set wwan0 down		# change the wwan0 to the one returned above if different
echo 'Y' | sudo tee /sys/class/net/wwan0/qmi/raw_ip
sudo ip link set wwan0 up
sudo qmicli -p -d /dev/cdc-wdm0 --device-open-net='net-raw-ip|net-no-qos-header' --wds-start-network="apn='internet',ip-type=4" --client-no-release-cid

sudo udhcpc -i wwan0
ip a s wwan0
ip r s

ping -4 www.google.com
