# AVX Search

- a fork of https://github/kwonus/Digital-AV

It's been a quarter century since the first release of AV-Bible for Windows. In its day, it was the world's first <u>free</u> bible software with a graphical user interface that ran on Microsoft Windows. This "Freeware" was maintained for a decade and a half (AV-1995, AV-1996, AV-1997, ..., AV-2011). Eventually, it evolved into a software development kit (SDK). Accordingly, it was renamed Digital-AV some years ago.

You can rely on its foundation, with countless deployments and extensive text validation. Digital-AV has travelled the world and back with feedback from Christian missionaries, pastors, and lay people. They used it in their ministries. In return, I received treasured quality-control feedback. By 2008, all of the textual bugs were ironed out. Not coincidentally, 2008 was the first release of the SDK. Never making a dime, and pouring a healthy chunk of my life into this effort: this has been a labor of love.

AVX-Search represents a radical step forward at the same time as it reaches back to its roots as the fastest and most compact search tool for the KJV text. This fork from Digital-AV assembles all the pieces into a whole.

The Digital-AV SDK is a single 19mb file that can be used to manifest the entire text of the bible, including Strong's numbers, Lemmatizations, Part-of-Speech tags, and other linguistic features. But even with all of that, it's still the KJV Bible at the core. AVX-Search replaces the C++ foundations of the Digital-AV SDK with a highly-efficient and compact, file-based implementation in C++ named AVX-Lib, also found in this repo. Herein can be found the revised/upgraded AVX-Omega-3911 data file of the Digital-AV Omega SDK. Coupling AVX-Search with the open sources we produce a fast and efficient search engine, fully optimized for the sacred text, with a spartan set of dependencies. We even handle fuzzy string matching to provide rich user-facing applications.

There is one external dependency of AVX-Search: that is FlatBuffers. It was selected for its speed, compactness, ubiquity, and its liberal licence. It is used for communication with the Blueprint-Blue parser/server.

Of course, there are several internal dependencies. These are all open source projects, produced and managed by AV Text Ministries [https://github/kwonus]. There was no need to fork these other dependencies [purple boxes below]; these are already complete and generally available. However, an adaption of the C# AVXLib to the latest Omega-3911 release is a current work in progress.

Another expected tweak to the Blueprint-Blue server is expected: We hope to migrate its interface from Named-Pipes to HTTPS-REST. It will still utilize Flatbuffers, but HTTPS will make it handle non-Windows clients.  It is also updated to deliver the newly released AVX [phonetic] Lexicon that exposes all AVX lexical entries using NUPhone [phonetic] representations.

How each dependent service and library are inter-related, with respect to AVX-Search is depicted in this diagram:

![](AVXSearch/AVXSearch-context.png)

The blue boxes above are all in active development with the planned completion identified in the diagram; All of these can be found in this [AVX] repo. The purple boxes are already complete from a developer perspective. However, they still need to be packaged for deployment.  End-user apps are unavailable at this time. They are expected to become available in late 2023 or early in 2024. After that, status will be evaluated and work can commence on the gray boxes.  It's helpful to have this pic as a roadmap. As you can see, AVX-Search is a central dependency for downstream user-facing apps. For additional info on the purple boxes and Digital-AV, head on over to  https://github.com/kwonus, and browse the repos there.

While the AV-Bible application name was resurrected as a C# WPF application (available at the Windows Store as a free app), the current plan is to re-wire AV-Bible to utilize the soon to be available fast and efficient native C++ library.

The Lord gave the word: great was the company of those that published it. -- Psalm 68:11
