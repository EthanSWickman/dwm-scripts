<p>jifbar is a Simple Status Bar Used with DWM on Arch Linux Systems</p>

<h1>Dependencies</h1>
<ul>

<li>pacman-contrib package</li>

</ul>

<h1>Install</h1>
<ol>

<li>run make and then make install as root</li>

</ol>

<h1>Uninstall</h1>
<ol>

<li>run make uninstall as root</li>

</ol>

<h1>Todo</h1>
<ul>

<li>migrate monitors from systemd timers to native jifbar by using asynchronous system calls to update monitor files, right now there is a bug with the checkupdates timer script not always working</li>
<li>test speed of counter array instead of modulus update management, and change to it if it is faster (it will be)</li>
<li>come up with universal solution for network usage status (detect the in use network card(s) and monitor them instead of just my Thinkpad card wlan0)</li>
<li>keep network speed string to a certain number of characters so it doesn't bounce the bar around constantly</li>
<li>create config file that uses compile time constants to kill unwanted features on the bar</li>

</ul>

