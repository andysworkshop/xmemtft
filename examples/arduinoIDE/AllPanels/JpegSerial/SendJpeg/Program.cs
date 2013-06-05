using System;
using System.IO.Ports;
using System.IO;

namespace SendJpeg {

  /*
   * main program class. example usage:
   *   sendjpeg.exe mytest.jpg com5 1000000 63
   */
  
  class Program {
    static void Main(string[] args) {

      try {
        if (args.Length != 4) {
          Console.WriteLine("usage: sendjpeg <jpegfile> <com-port> <baud-rate> <chunk-size>");
          return;
        }

        // open the port

        Console.WriteLine("Opening port "+args[2]);
        SerialPort serialPort = new SerialPort(args[1],int.Parse(args[2]),Parity.None,8,StopBits.One);
        serialPort.Handshake = Handshake.None;
        serialPort.Open(); 

        // get the size of the file to send

        FileInfo fi=new FileInfo(args[0]);
        long size=fi.Length;
        Console.WriteLine("Writing file size ("+size+") bytes");

        // send the file size, LSB first

        byte[] buffer=new byte[4];

        buffer[3]=(byte)((size >> 24) & 0xff);
        buffer[2]=(byte)((size >> 16) & 0xff);
        buffer[1]=(byte)((size >> 8) & 0xff);
        buffer[0]=(byte)(size & 0xff);

        serialPort.Write(buffer,0,4);

        // get ready to send the file

        buffer=new byte[1000];
        long remaining=size;
        int count,value;
        int chunkAvailable,chunkSize=int.Parse(args[3]);

        Console.WriteLine("Writing file data");

        using(BufferedStream bs=new BufferedStream(new FileStream(args[0],FileMode.Open,FileAccess.Read))) {
        
          chunkAvailable=chunkSize;

          while(remaining>0) {

            // read either 1000 or what's left

            count=(int)(remaining<1000 ? remaining : 1000);
            bs.Read(buffer,0,count);

            for(int i=0;i<count;i++) {

              // send a byte

              serialPort.Write(buffer,i,1);

              // if we have just sent the last of a chunk, wait for the ack

              if(--chunkAvailable==0) {
                value=serialPort.ReadByte();
                if(value!=0xaa)
                  throw new Exception("Unexpected chunk acknowledgement");

                // new chunk on its way

                chunkAvailable=chunkSize;
              }
            }

            remaining-=count;
            Console.Write(".");
          }
        }
        Console.WriteLine("\nDone.");
      }
      catch(Exception ex) {
        Console.WriteLine(ex.ToString());
      }
    }
  }
}
