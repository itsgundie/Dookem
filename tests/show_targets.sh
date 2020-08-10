printf "\033[38;2;200;150;200mHey!\n
Here's your daily tasks:\n"
printf "$(cat -n tasks.txt | sed "s/RED /\\\033[38;2;200;50;100m/g" | \
      sed 's/YELL /\\\033[38;2;200;200;0m/' | \
      sed 's/GREEN /\\\033[38;2;0;200;0m/')\033[38;2;200;150;200m\n"
printf "\033[38;2;200;150;200mDo you wanna add some more?\n"
printf "\033[38;2;50;150;50my/\033[38;2;200;50;100mn\n\033[38;2;200;150;200m"
read varname
if [ $varname = y ]
then echo "Enter new tasks with desired mark:"
printf "\033[38;2;200;50;100mRED - high priority, "
printf "\033[38;2;200;200;0mYELL - medium, \033[38;2;0;200;0mGREEN - wishlist.\033[38;2;200;150;200m\n"
echo "Write END when at the end of list."
while [ "$varname" != END ] && [ "$varname" != end ]; do
    read -r varname
    if [ "$varname" != END ] && [ "$varname" != end ]
    then echo "$varname" >> tasks.txt
    fi
done
rm -rf tasks.txt-e
printf "$(cat -n tasks.txt | sed "s/RED /\\\033[38;2;200;50;100m/g" | \
      sed 's/YELL /\\\033[38;2;200;200;0m/' | \
      sed 's/GREEN /\\\033[38;2;0;200;0m/')\033[38;2;200;150;200m\n"
fi
