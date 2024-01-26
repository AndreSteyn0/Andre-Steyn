// experience.component.ts
import { AfterViewInit, Component, Inject, OnInit, PLATFORM_ID } from '@angular/core';
import { Router, RouterLink, RouterLinkActive } from '@angular/router';
import { ScrollService } from '../../services/scroll.service';
import { ViewportScroller, isPlatformBrowser } from '@angular/common';
import AOS from 'aos';
import 'aos/dist/aos.css';

@Component({
  selector: 'app-experience',
  standalone: true,
  imports: [RouterLink, RouterLinkActive],
  templateUrl: './experience.component.html',
  styleUrl: './experience.component.css',
})
export class ExperienceComponent implements AfterViewInit, OnInit{
  constructor(
    @Inject(PLATFORM_ID) private platformId: Object,
    private scrollService: ScrollService,
    private router: Router,
    private viewportScroller: ViewportScroller
  ) {}

  ngOnInit(): void {
    if (isPlatformBrowser(this.platformId)) {
      AOS.init();
    }
  }
  
  ngAfterViewInit() {
    this.scrollService.scrollObservable.subscribe((section) => {
      setTimeout(() => {
        this.scrollToElement(section);
      }, 0);
    });
  }

  scrollToElement(section: string) {
    const element = document.getElementById(section);
    if (element) {
      this.viewportScroller.scrollToAnchor(element.id);
    }
  }

  onClickReadMore(section: string, navigateTo: string) {
    this.scrollService.scrollTo(section);
    this.router.navigate([navigateTo]);
  }
}
