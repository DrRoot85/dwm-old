#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/local/X11/xinit/.Xresources
sysmodmap=/etc/local/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/local/X11/xinit/xinitrc.d ] ; then
 for f in /etc/local/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

#twm &
#xclock -geometry 50x50-1+1 &
#xterm -geometry 80x50+494+51 &
#xterm -geometry 80x20+494-0 &
#exec xterm -geometry 80x66+0+0 -name login

####### Lang ######
export LC_ALL=en_US.UTF-8
export MM_CHARSET=UTF-8
export LANG=en_US.UTF-8
export LANGUAGE=en_US.UTF-8
export GTK2_RC_FILES="$HOME/.gtkrc-2.0"
export BROWSER=firefox
#setxkbmap us
export QT_QPA_PLATFORMTHEME="qt5ct"
MOZ_X11_EGL=1
xset s off
xset -dpms
xset s noblank
#xautolock -time 10 -locker slock
export GVFS_DISABLE_FUSE=1

#Audio
#/usr/bin/pipewire &
#/usr/bin/pipewire-pulse &
#/usr/bin/wireplumber &

## Nvidia ##
#xrandr --setprovideroutputsource modesetting NVIDIA-0
#xrandr --auto

### Pywal ###
# Add this to your .xinitrc or whatever file starts programs on startup.
# -R restores the last colorscheme that was in use.
wal -R

##Set New Wall
autowall &

# Bat Noti
#batterynotify &

## DWM ##
while :; do
	dbus-launch dwm
done
# relaunch DWM if the binary changes, otherwise bail
#csum=""
#new_csum=$(sha1sum $(which dwm))
#while true
#do
#    if [ "$csum" != "$new_csum" ]
#    then
#        csum=$new_csum
#        dwm
#    else
#        exit 0
#    fi
#    new_csum=$(sha1sum $(which dwm))
#    sleep 0.5
#done
