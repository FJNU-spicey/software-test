package hotel;

import java.util.Scanner;
public class MainRun {
	private static ListHome lh=new ListHome();// 表示房间
	private static InHotel ih=null;
	private static OutHotel oh=null;
	static DP dp=new DP();
	 static IData id =dp;
    	public static void main(String[] args) {
      		
		id.iniRooms();
		Command();
	}
	private static  void Command() {
		String comm;// 表示用户输入的命令
		Scanner sca=new Scanner(System.in);
		while (true) {
			System.out.println("请输入命令：");
			System.gc();
			comm = sca.next();
			if ("search".equalsIgnoreCase(comm)) {
				lh.search();
			} else if ("in".equalsIgnoreCase(comm)) {
				int roomNo = sca.nextInt();
				try{
				if( validRoomNo(roomNo)){
					String name = sca.next();
					ih=new InHotel(id);
					System.out.println(ih.in(roomNo, name));
					}else
				      System.out.println("房间号错!");
				}catch(Exception e)
				{
					System.out.println(e.toString());
				}
				
			} else if ("out".equalsIgnoreCase(comm)) {
				int roomNo = sca.nextInt();
				if( validRoomNo(roomNo)){
					
					oh=new OutHotel(id);
					System.out.println(oh.out(roomNo));
					}else
						System.out.println("房间号错!");
													
			} else if ("exit".equalsIgnoreCase(comm)) {
				System.out.println("程序退出...");
				break;
			} else {
				System.out.println("命令输入错误，请重新输入：");
			}
			
		}
		sca.close();
		
	}
	private static  boolean validRoomNo(int roomNo){
		if((roomNo/100>10)||(roomNo/100<1)||(roomNo%100>12)||(roomNo%100<1))
			{
				return false;}
			else 
				{return true;}		
	}
	
}

