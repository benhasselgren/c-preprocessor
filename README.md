<h1>Preprocess Application</h1>
<h6>Author: Ben Hasselgren</h6>
<h6>Matric No.: 40416405</h6>
<h6>Date: 19/02/2019</h6>

<h3>Description</h3>

<p>This program allows users to preprocess .c files. You type in the command line the file you want to process and the program will return a .o file which has been preprocessed.</p>

<h3>Tool chain required</h3>
<p>Microsoft compiler (Visual Studio 2017 developer command prompt)</p>

<h3>How to build (from source)</h3>
<ol>
<li>Navigate to directory contaiing the source files.</li>
<li>Type in the following commands to build the file.</li>
	<code>
	cl /c check-comment.c check-pre-processor-word.c check-define-variable.c<br>
	lib /OUT:pre-processor.lib check-comment.obj check-pre-processor-word.obj check-define-variable.obj<br>
	cl /c preprocess.c<br>
	link preprocess.obj pre-processor.lib
	</code>
<li>Now you are ready to use the application.</li>
</ol>

<h3>How to build (using makefile) - <bold>This is the method recommended to build the application</bold></h3>
<ol>
<li>Navigate to directory contaiing the source files.</li>
<li>Type in the following commands to build the file.</li>
	<code>
	nmake init-app
	</code>
<li>Now you are ready to use the application.</li>
</ol>

<h3>How to use</h3>
<ol>
<li>To preprocess a file <bold>without</bold> comments use:</li>
	<code>
	preprocess -i 'name-of-file'.c
	</code>
<li>To preprocess a file <bold>with</bold> comments use:</li>
	<code>
	preprocess -i 'name-of-file'.c -c
	</code>
</ol>
