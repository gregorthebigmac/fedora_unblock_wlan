#!/bin/bash

make && \
sudo cp keep_bt_down /usr/bin/keep_bt_down && \
sudo cp keep_bt_down.service /lib/systemd/system/keep_bt_down.service && \
sudo systemctl enable keep_bt_down.service && \
sudo systemctl start keep_bt_down.service && \
systemctl status keep_bt_down.service
