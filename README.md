# AVX Search

- a fork of https://github/kwonus/Digital-AV

It's been over twenty-five years since the release of AV-Bible for Windows. In its day, it was the first free bible software with a graphical user interface that ran on Microsoft Windows. This "Freeware" was maintained for a decade and a half (AV-1995, AV-1996, AV-1997, ..., AV-2011). Eventually, it evolved into a software development kit (SDK). Accordingly, it was renamed Digital-AV some years ago.

You can rely on its foundation, with countless deployments and extensive text validation. Digital-AV has travelled the world and back with feedback from Christian missionaries. They used it in their ministries. In return, I received treasured quality-control feedback. By 2008, all of the textual bugs had been ironed out. Not coincidentally, 2008 was the first release of the SDK. Never making a dime, and pouring a healthy chuck of my life into it: this has been a labor of love.

AVX-Search represents a radical step forward at the same time as it reaches back to its roots as the fastest and most compact search tool for the KJV text. This fork from Digital-AV assembles all the pieces into a whole.

The Digital-AV SDK is a single 19mb file that can be used to manifest the entire text of the bible, including Strong's numbers, Lemmatizations, Part-of-Speech tags, and other linguistic features. But even with all of that, it's still the KJV Bible at the core. AVX-Search utilizes the C++ foundations of that SDK. Coupling that with some open source parsing engines, results in a fast and efficient search engine with a minimal set of dependencies. Upon this, is built user-facing applications.

One dependency that is rolled in here is FlatBuffers, due to its speed, compactness, and ubiquity.

The other dependencies are open source projects, produced and managed by AV Text Ministries. [https://github/kwonus]

How they relate to AVX-Search is depicted in this diagram:

![](AVXSearch/AVXSearch-context.png)

The blue boxes above are all in active development with a planned completion this year; All of these efforts can be found in this [AVX] repo. The purple boxes are already complete from a developer perspective. However, they still need to be packaged for deployment.  End-user apps are unavailable at this time. They are expected to become available in 2023: Q3 or Q4. After that, status will be evaluated and work can commence on the gray boxes.  It's helpful to have this pic as a roadmap. As you can see, AVX-Search is a central dependency for downstream user-facing apps. The current architecture reflects a mitigation of a recent surprising discovery: dotnet apps are unable to perform interop with x64 C++ libraries via P/Invoke. Accordingly, the revised architecture diminishes the overall presence of dotnet. Hello C++! Another mitigation for the short term is to produce Windows-only desktop apps. This limitation was useful as Windows named pipes are the current workaround for fast IPC between 64-bit Windows compiled binaries and dotnet 7 C# apps. For additional info on the purple boxes and Digital-AV, head on over to  https://github.com/kwonus, and browse the repos there.

The Lord gave the word: great was the company of those that published it. -- Psalm 68:11
