# teensy_rake

Teensy rake is a rake-based build system which is intended to accomplish multi-targeting of embedded devices. It was built for learners wishing to follow [this tutorial on using TDD for embedded development](http://sunetrike.com/open-source/embedded/teensy/a-test-drive-build-system-for-teensy/)

The Rakefile was built via TDD and it employs an embedded-TDD process according to the frameworks laid out by:
  - James Grenning's [TDD for Embedded Systems](https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/)
  - The [sample rakefile](https://github.com/ThrowTheSwitch/Unity/tree/master/examples/example_3) provided by Throw the Switch (Creator of Unity)
  - [Electron Vector's articles](http://www.electronvector.com/blog/using-rake-to-build-a-simple-c-application) on using GCC to compile and assemble C-projects

It has been built for instructional purposes with two primary goals:
 1. to give Arduino developers an introduction into the world of Embedded TDD
 2. to achieve a multi-targetting buildchain that allows a developer to build an embedded TDD-application that can be ported to multiple devices from multiple vendors

 The first goal is executed on via this blog post. So if you are an Arduino developer interested in levelling up your C-programming skills, you can start with this [blog post](http://sunetrike.com/open-source/embedded/teensy/a-test-drive-build-system-for-teensy/)*

 The second goal is admittedly more ambitious and may very well be a bigger challenge than my time and programming skills can deliver on.

 All said, I have gotten a lot out of this exercise and the blog post is basically what I wish I would have found after completing Grenning's book the first time. Embedded systems force a lot of learning on you at once.  I've attempted to distill this down into a bite-sized chunk of learning and I hope it will also help others on a similar path.

 Cheers!

teensy build and unity can be [downloaded here](https://drive.google.com/file/d/1RSY28QoYkp5Jy6VnWHMu4gSzKXTkfinh/view?usp=drive_link).  just paste it into the root of the project folder
 
