#!/bin/bash

#Function for reading tags and values
getvalue () {
	local IFS='>'
	read -d '<' TAG VALUE
}

#Load new RSS file
wget -O /home/pi/unix/rss/rss --post-data=authpw=<wiki_password_here> <wiki_address_here>

#Remove data from last use
rm /home/pi/unix/rss/rss_parse
echo "" > /home/pi/unix/rss/rss_json.json

#While loop to parse data from RSS file
NUMBEROFITEMS="0"
cat /home/pi/unix/rss/rss | while getvalue ; do
	case $TAG in
		'item')
			title=''
			contributor=''
			pubDate=''
			;;
		'title')
			title="$VALUE"
			;;
		'dc:contributor')
			contributor="$VALUE"
			;;
		'pubDate')
			pubDate="$VALUE"
			;;
		'/item')
			echo "$title;$contributor;$pubDate;" >> /home/pi/unix/rss/rss_parse
			let "NUMBEROFITEMS++"
			;;
	esac
#Update number of items in rss file to a file
#echo "$NUMBEROFITEMS" > /home/pi/unix/rss/number_of_items
done

#Execute c++ program
/home/pi/unix/rss/program

#Send data to Slack
curl -X POST -d '@/home/pi/unix/rss/rss_json.json' <url_and_authentication_for_slack_here>
