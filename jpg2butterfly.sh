## large
for IMAGE in $(ls -1 --color=never butterflies/*.JPG); do printf "===$IMAGE================\n"; jp2a --background=light --width=180 --height=65 --chars="  -+:=7142%98" $IMAGE; done >  bfly_large.txt
for IMAGE in $(ls -1 --color=never butterflies/*.jpg); do printf "===$IMAGE================\n"; jp2a --background=light --width=180 --height=65 --chars="  -+:=7142%98" $IMAGE; done >> bfly_large.txt

## bigger
for IMAGE in $(ls -1 --color=never butterflies/*.JPG); do printf "===$IMAGE================\n"; jp2a --background=light --width=140 --height=55 --chars="  -+:=7142%98" $IMAGE; done >  bfly_bigger.txt
for IMAGE in $(ls -1 --color=never butterflies/*.jpg); do printf "===$IMAGE================\n"; jp2a --background=light --width=140 --height=55 --chars="  -+:=7142%98" $IMAGE; done >> bfly_bigger.txt

## medium
for IMAGE in $(ls -1 --color=never butterflies/*.JPG); do printf "===$IMAGE================\n"; jp2a --background=light --width=100 --height=45 --chars="  -+:=7142%98" $IMAGE; done >  bfly_medium.txt
for IMAGE in $(ls -1 --color=never butterflies/*.jpg); do printf "===$IMAGE================\n"; jp2a --background=light --width=100 --height=45 --chars="  -+:=7142%98" $IMAGE; done >> bfly_medium.txt

## small  
for IMAGE in $(ls -1 --color=never butterflies/*.JPG); do printf "===$IMAGE================\n"; jp2a --background=light --width=70  --height=30 --chars="  -+:=7142%98" $IMAGE; done >  bfly_small.txt
for IMAGE in $(ls -1 --color=never butterflies/*.jpg); do printf "===$IMAGE================\n"; jp2a --background=light --width=70  --height=30 --chars="  -+:=7142%98" $IMAGE; done >> bfly_small.txt

