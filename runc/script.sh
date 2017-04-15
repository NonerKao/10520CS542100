#!/bin/bash

set -x

NEWNETNS=net415
VETH_HOST=veth_4150
VETH_CONT=veth_4151
NEWBRIDGE=br415

BRADDR=10.5.7.1/24
VETHADDR=10.5.7.13/24
NEWROUTE=10.5.7.1
SUBDOMAIN=10.5.7.0/24

WAN=enp3s0

ip netns add $NEWNETNS
ip link add $VETH_HOST type veth peer name $VETH_CONT
ip link set $VETH_CONT netns $NEWNETNS

ip link add $NEWBRIDGE type bridge
ip link set $VETH_HOST master $NEWBRIDGE

ip addr add $BRADDR dev $NEWBRIDGE
ip netns exec $NEWNETNS ip addr add $VETHADDR dev $VETH_CONT
ip netns exec $NEWNETNS ip route add default via $NEWROUTE

ip link set $NEWBRIDGE up
ip link set $VETH_HOST up
ip netns exec $NEWNETNS ip link set $VETH_CONT up

iptables -A FORWARD -o $WAN -i $NEWBRIDGE -s $SUBDOMAIN -m conntrack --ctstate NEW -j ACCEPT
iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -t nat -A POSTROUTING -o $WAN -j MASQUERADE
