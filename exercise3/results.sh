
#cp /dev/null fitresults.txt 

REGION="barrel"  #write the name of the region you are analyzing

mkdir -p results/$REGION

HISTO_LIST=(deltaM_5 deltaM_6) #write the list of the plot name you need to fit
MACRO_LIST=(fit2bDATA.C fit4bDATA.C fit2bMC.C fit4bMC.C)

for file in ${HISTO_LIST[*]}; do
rm results/$REGION/${file}.txt

for macro in ${MACRO_LIST[*]}; do

sed -i -e "s/input_file/${file}/" $macro
sed -i -e "s/fitresults/${file}/" $macro
sed -i -e "s/results/results\\/${REGION}/" $macro
root -l $macro 
sed -i -e "s/${file}/input_file/" $macro
sed -i -e "s/results\\/${REGION}/results/" $macro
sed -i -e "s/${file}/fitresults/" $macro

done

done



