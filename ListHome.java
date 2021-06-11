package hotel;

public class ListHome {
	
	DP dp=new DP();
	IData id=dp;
	private long startTime=System.currentTimeMillis();
	private int thinkTime=0;
	public ListHome(int thinkTime){
		this.thinkTime=thinkTime;
	}
	public ListHome(){
		
	}
	public  void search() {
		
		for (int i = 0; i < HotelConstant.HOTEL_TOTAL_FLOOR; i++) {
			//打印房间号
 			for (int j = 0; j < HotelConstant.HOTEL_ROOMS_EVERYFLOOR; j++)
 
 {
				if (j + 1 < HotelConstant.HOTEL_TOTAL_FLOOR) {
					System.out.print(i + 1 + "0" + (j + 1) + "	");
				} else {
					System.out.print(i + 1 + "" + (j + 1) + "	");
				}
			}
			//打印房间状态
			System.out.println();
			for (int j = 0; j < HotelConstant.HOTEL_ROOMS_EVERYFLOOR; j++) {
				System.out.print(id.getStation((i+1)*100+j+1) + "	");			
				}		
			System.out.println();
		}
	try{Thread.sleep(thinkTime);} catch(Exception e){}
	long endTime=System.currentTimeMillis();
		System.out.println("Response Time:"+(endTime-startTime)+"Millisenconds");
	}
	
}
