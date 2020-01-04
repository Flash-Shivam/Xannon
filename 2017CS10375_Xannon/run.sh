
    #!/bin/bash
    # Basic if statement
    read a b c d 
    if [ $b -eq 8 ]
    then
    ./bot $a $b $c $d
    elif [ $c -eq 10 ]
    then ./bot3 $a $b $c $d
	 else 
		./bot2 $a $b $c $d
    fi


