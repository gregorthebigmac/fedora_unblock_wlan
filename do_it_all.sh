#!/bin/bash

make && \
sudo cp keep_wlan_up /usr/bin/keep_wlan_up && \
sudo cp keep_wlan_up.service /lib/systemd/system/keep_wlan_up.service && \
sudo systemctl enable keep_wlan_up.service && \
sudo systemctl start keep_wlan_up.service && \
systemctl status keep_wlan_up.service
