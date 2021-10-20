#! /bin/bash

while ( [ 1 ])
do
sleep 1

if ( pgrep minishell > /dev/null )
then
	if leaks minishell | grep LEAK > /dev/null 
	  then
			osascript -e 'tell app "System Events" to display dialog "LEAKS FOUND DUDE!!"' > /dev/null
			killall minishell
				# while (pgrep minishell > /dev/null)
				# do 
				# sleep 1
				# done
		fi

fi

done