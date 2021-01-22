#!/bin/bash 
ADAPTER_SINK_NAME=$( pactl list sinks | sed -n 's/^.*Name: \(.*\.usb.*\)$/\1/p' | head -n 1 ) 
echo setting $ADAPTER_SINK_NAME
pactl set-default-sink $ADAPTER_SINK_NAME

for SINK_ID in $(pactl list sink-inputs | sed -n 's/^Sink Input #\([0-9]*\)$/\1/p')
do
    echo Sink $SINK_ID
    pactl move-sink-input $SINK_ID $ADAPTER_SINK_NAME
    pactl move-sink-input $SINK_ID adapter-soft-volume
done
echo exporting settings and moveing to usb sound device [done].
echo reuuning recheck and exiting script now..
export LC_ALL=C
ADAPTER_SINK_NAME=$( pacmd list-sinks | sed -n 's/^.*name: <\([^>]*\.usb[^>]*\)>$/\1/p' | head -n 1 )

if [[ -z "${ADAPTER_SINK_NAME:-}" ]]
then
    ADAPTER_SINK_NAME=$( pactl list sinks | sed -n 's/^.*Name: \(.*\.usb.*\)$/\1/p' | head -n 1 ) 
fi

echo will plug on $ADAPTER_SINK_NAME
pactl set-default-sink $ADAPTER_SINK_NAME
pacmd unload-module module-combine 
pacmd load-module module-combine sink_name=adapter-soft-volume slaves=$ADAPTER_SINK_NAME
pactl set-default-sink adapter-soft-volume
echo done.. exiting script.

