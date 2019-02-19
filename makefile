init-app:
		cl /c check-comment.c check-pre-processor-word.c check-define-variable.c
		lib /OUT:pre-processor.lib check-comment.obj check-pre-processor-word.obj check-define-variable.obj
		cl /c preprocess.c
		link preprocess.obj pre-processor.lib
		
create-string-file:
		preprocess -i string_functions.c
		
create-string-file-c:
		preprocess -i string_functions.c -c
		
create-math-file:
		preprocess -i math_functions.c
		
create-string-file-c:
		preprocess -i math_functions.c -c
		
clean:
		del *.obj
		del *.exe
		del *.asm
		del *.o