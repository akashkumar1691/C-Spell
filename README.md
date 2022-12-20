# philspel
a very simple and silly spelling checker

<p>The program
accepts a single command line argument, the name of a dictionary to
use. For example, to use philspel, all you would need to type into the terminal is:</p>
<div class="language-console highlighter-rouge"><div class="highlight"><pre class="highlight"><code><span class="gp">$</span><span class="w"> </span>./philspel dictionary.txt
</code></pre></div></div>
<p>Of course, you can replace <code class="language-plaintext highlighter-rouge">dictionary.txt</code> with whichever file you wish to use for your dictionary.</p>

<p>This dictionary consists of a list of valid words to use in
checking the input.  <code class="language-plaintext highlighter-rouge">philspel</code> processes standard input and
copies it to standard output.  For each word (sequence of letters
unbroken by any non-letter character) in the input, <code class="language-plaintext highlighter-rouge">philspel</code> looks for all of the following variations of the word in its dictionary:</p>
<ol>
  <li>The word itself.</li>
  <li>The word converted entirely to lowercase letters</li>
  <li>The word with all but the first letter converted to lowercase.</li>
</ol>

<p>If any of the three variations are found in the dictionary, the word is copied directly to
standard output.  Otherwise, the word is copied to standard output,
with the string <code class="language-plaintext highlighter-rouge">" [sic]"</code> (without the quotation marks
but <em>with the spaces</em> appended.  All other input (e.g. whitespace) is copied to standard
output unchanged.</p>
