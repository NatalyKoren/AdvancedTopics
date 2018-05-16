import os
import shutil
import time
import errno


def runTestsBetter():
	#timestamp = str(time.strftime("%d%m%Y-%H%M%S"))
	timestamp = "ex2"
	wd = os.getcwd()
	alltests = os.path.join(wd, "tests")
	print("runTests started")
	inputFiles = ["player1.rps_board","player2.rps_board","player1.rps_moves","player2.rps_moves"]

	for testDir in os.listdir(alltests):
		testDir_full = os.path.join(alltests, testDir)
		if os.path.isdir(testDir_full) and testDir.startswith("test"):
			print("Testing: " + testDir)

			#copy input files to working directory
			for file in inputFiles:
                                try:
                                        os.remove(file)
                                except OSError as e:
                                        if e.errno != errno.ENOENT:
                                                raise
                                filePath = os.path.join(testDir_full,file)
                                if(os.path.exists(filePath)):
                                        shutil.copy(filePath ,file)

			#running game
			consoleOutputFile = os.path.join(testDir_full, "{}_crps.consoleoutput".format(timestamp))
			os.system("ex2 file-vs-file > \"{}\"".format(consoleOutputFile))

			#put timestamped output file in test dir
			shutil.copy("rps.output",os.path.join(testDir_full, "{}_rps.output".format(timestamp)))

			print("\t done\n__________\n")




print("Python Script")
print("Run Tests")
runTestsBetter()
print("Done Script")
